#ifndef OGREAPPLOGIC_H
#define OGREAPPLOGIC_H

#include <OgrePrerequisites.h>
#include <OgreStringVector.h>
#include <OIS/OIS.h>

#include "CanvasTexture.h"
#include "Chrono.h"

class OgreApp;
class StatsFrameListener;

class OgreAppLogic
{
public:
	OgreAppLogic();
	~OgreAppLogic();

	void setParentApp(OgreApp *app) { mApplication = app; }

	/// Called before Ogre and everything in the framework is initialized
	/// Configure the framework here
	bool preInit(const Ogre::StringVector &commandArgs);
	/// Called when Ogre and the framework is initialized
	/// Init the logic here
	bool init(void);

	/// Called before everything in the framework is updated
	bool preUpdate(Ogre::Real deltaTime);
	/// Called when the framework is updated
	/// update the logic here
	bool update(Ogre::Real deltaTime);

	/// Called before Ogre and the framework are shut down
	/// shutdown the logic here
	void shutdown(void);
	/// Called when Ogre and the framework are shut down
	void postShutdown(void);

	void createSceneManager(void);
	void createViewport(void);
	void createCamera(void);
	void createScene(void);

	bool processInputs(Ogre::Real deltaTime);

protected:
	// OGRE
	OgreApp *mApplication;
	Ogre::SceneManager *mSceneMgr;
	Ogre::Viewport *mViewport;
	Ogre::Camera *mCamera;

	StatsFrameListener *mStatsFrameListener;

	// OIS
	class OISListener : public OIS::MouseListener, public OIS::KeyListener
	{
	public:
		virtual bool mouseMoved( const OIS::MouseEvent &arg );
		virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
		virtual bool keyPressed( const OIS::KeyEvent &arg );
		virtual bool keyReleased( const OIS::KeyEvent &arg );
		OgreAppLogic *mParent;
	};
	friend class OISListener;
	OISListener mOISListener;

	// Canvas	
	void createCanvasOverlay();
	void updateCanvas();
	void updateClock1Canvas();
	void updateClock2Canvas();
	void updateSunCanvas();
	void createCanvasCube(void);
	Ogre::ManualObject* createCubeMesh(const std::string& name, const std::string& matName);

	Ogre::Canvas::Texture* mCanvasTextureClock1;
	Ogre::Canvas::Texture* mCanvasTextureClock2;
	Ogre::Canvas::Texture* mCanvasTextureSun;
	Ogre::Image mSun;
	Ogre::Image mEarth;
	Ogre::Image mMoon;
	Chrono mChrono;
};

#endif // OGREAPPLOGIC_H