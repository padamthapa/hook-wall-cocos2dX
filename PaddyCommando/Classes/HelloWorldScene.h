//
//  HelloWorldScene.h
//  PaddyCommando
//
//  Created by padam on 28/09/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};

class SimpleQueryCallback : public b2QueryCallback
{
public:
    b2Vec2 pointToTest;
    b2Fixture * fixtureFound;
    
    SimpleQueryCallback(const b2Vec2& point) {
        pointToTest = point;
        fixtureFound = NULL;
    }
    
    bool ReportFixture(b2Fixture* fixture) {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_staticBody) {
            if (fixture->TestPoint(pointToTest)) {
                fixtureFound = fixture;
                return true;
            }
        }
        return false;
    }
};

class HelloWorld : public cocos2d::CCLayer {
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    // adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(float dt);
    
private:
    b2World* world;
    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    
    GLESDebugDraw* m_debugDraw;
    b2Body *hero;
    b2DistanceJoint *distanceJoint;
    bool isHooked = false;
    
    void fireHook(const cocos2d::CCPoint location);
    void releaseHook();
    void manageHook();
    static bool queryCallback(b2Fixture fixture);
    b2Body* addBox(int pX, int pY, int w, int h, b2BodyType bodyType);
    int generateRandomBetween(int min, int max);
};

#endif // __HELLO_WORLD_H__
