#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Initialised; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  fgInitialiseInputDevices () ; 
 TYPE_1__ fgState ; 

__attribute__((used)) static void fghInitialize( const char* displayName )
{
#if TARGET_HOST_POSIX_X11
    fgDisplay.Display = XOpenDisplay( displayName );

    if( fgDisplay.Display == NULL )
        fgError( "failed to open display '%s'", XDisplayName( displayName ) );

    if( !glXQueryExtension( fgDisplay.Display, NULL, NULL ) )
        fgError( "OpenGL GLX extension not supported by display '%s'",
            XDisplayName( displayName ) );

    fgDisplay.Screen = DefaultScreen( fgDisplay.Display );
    fgDisplay.RootWindow = RootWindow(
        fgDisplay.Display,
        fgDisplay.Screen
    );

    fgDisplay.ScreenWidth  = DisplayWidth(
        fgDisplay.Display,
        fgDisplay.Screen
    );
    fgDisplay.ScreenHeight = DisplayHeight(
        fgDisplay.Display,
        fgDisplay.Screen
    );

    fgDisplay.ScreenWidthMM = DisplayWidthMM(
        fgDisplay.Display,
        fgDisplay.Screen
    );
    fgDisplay.ScreenHeightMM = DisplayHeightMM(
        fgDisplay.Display,
        fgDisplay.Screen
    );

    fgDisplay.Connection = ConnectionNumber( fgDisplay.Display );

    /* Create the window deletion atom */
    fgDisplay.DeleteWindow = fghGetAtom("WM_DELETE_WINDOW");

    /* Create the state and full screen atoms */
    fgDisplay.State           = None;
    fgDisplay.StateFullScreen = None;

    if (fghNetWMSupported())
    {
      const Atom supported = fghGetAtom("_NET_SUPPORTED");
      const Atom state     = fghGetAtom("_NET_WM_STATE");
      
      /* Check if the state hint is supported. */
      if (fgHintPresent(fgDisplay.RootWindow, supported, state))
      {
        const Atom full_screen = fghGetAtom("_NET_WM_STATE_FULLSCREEN");
        
        fgDisplay.State = state;
        
        /* Check if the window manager supports full screen. */
        /**  Check "_NET_WM_ALLOWED_ACTIONS" on our window instead? **/
        if (fgHintPresent(fgDisplay.RootWindow, supported, full_screen))
        {
          fgDisplay.StateFullScreen = full_screen;
        }
      }
    }

#elif TARGET_HOST_MS_WINDOWS

    WNDCLASS wc;
    ATOM atom;

    /* What we need to do is to initialize the fgDisplay global structure here. */
    fgDisplay.Instance = GetModuleHandle( NULL );

    atom = GetClassInfo( fgDisplay.Instance, _T("FREEGLUT"), &wc );

    if( atom == 0 )
    {
        ZeroMemory( &wc, sizeof(WNDCLASS) );

        /*
         * Each of the windows should have its own device context, and we
         * want redraw events during Vertical and Horizontal Resizes by
         * the user.
         *
         * XXX Old code had "| CS_DBCLCKS" commented out.  Plans for the
         * XXX future?  Dead-end idea?
         */
        wc.lpfnWndProc    = fgWindowProc;
        wc.cbClsExtra     = 0;
        wc.cbWndExtra     = 0;
        wc.hInstance      = fgDisplay.Instance;
        wc.hIcon          = LoadIcon( fgDisplay.Instance, _T("GLUT_ICON") );

#if defined(_WIN32_WCE)
        wc.style          = CS_HREDRAW | CS_VREDRAW;
#else
        wc.style          = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
        if (!wc.hIcon)
          wc.hIcon        = LoadIcon( NULL, IDI_WINLOGO );
#endif

        wc.hCursor        = LoadCursor( NULL, IDC_ARROW );
        wc.hbrBackground  = NULL;
        wc.lpszMenuName   = NULL;
        wc.lpszClassName  = _T("FREEGLUT");

        /* Register the window class */
        atom = RegisterClass( &wc );
        FREEGLUT_INTERNAL_ERROR_EXIT ( atom, "Window Class Not Registered", "fghInitialize" );
    }

    /* The screen dimensions can be obtained via GetSystemMetrics() calls */
    fgDisplay.ScreenWidth  = GetSystemMetrics( SM_CXSCREEN );
    fgDisplay.ScreenHeight = GetSystemMetrics( SM_CYSCREEN );

    {
        HWND desktop = GetDesktopWindow( );
        HDC  context = GetDC( desktop );

        fgDisplay.ScreenWidthMM  = GetDeviceCaps( context, HORZSIZE );
        fgDisplay.ScreenHeightMM = GetDeviceCaps( context, VERTSIZE );

        ReleaseDC( desktop, context );
    }

    /* Set the timer granularity to 1 ms */
    timeBeginPeriod ( 1 );

#endif

    fgState.Initialised = GL_TRUE;

    /* InputDevice uses GlutTimerFunc(), so fgState.Initialised must be TRUE */
    fgInitialiseInputDevices();
}