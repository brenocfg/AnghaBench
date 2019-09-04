#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int DisplayMode; } ;
struct TYPE_6__ {int DoubleBuffered; } ;
struct TYPE_7__ {TYPE_1__ Window; } ;
typedef  TYPE_2__ SFG_Window ;
typedef  int /*<<< orphan*/  GLboolean ;

/* Variables and functions */
 int GLUT_DOUBLE ; 
 int /*<<< orphan*/  GL_FRONT ; 
 int /*<<< orphan*/  fgSetWindow (TYPE_2__*) ; 
 TYPE_3__ fgState ; 
 int /*<<< orphan*/  glDrawBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glReadBuffer (int /*<<< orphan*/ ) ; 

void fgOpenWindow( SFG_Window* window, const char* title,
                   GLboolean positionUse, int x, int y,
                   GLboolean sizeUse, int w, int h,
                   GLboolean gameMode, GLboolean isSubWindow )
{
#if TARGET_HOST_POSIX_X11
    XVisualInfo * visualInfo;
    XSetWindowAttributes winAttr;
    XTextProperty textProperty;
    XSizeHints sizeHints;
    XWMHints wmHints;
    unsigned long mask;
    unsigned int current_DisplayMode = fgState.DisplayMode ;

    /* Save the display mode if we are creating a menu window */
    if( window->IsMenu && ( ! fgStructure.MenuContext ) )
        fgState.DisplayMode = GLUT_DOUBLE | GLUT_RGB ;

    window->Window.FBConfig = fgChooseFBConfig( );

    if( window->IsMenu && ( ! fgStructure.MenuContext ) )
        fgState.DisplayMode = current_DisplayMode ;

    if( ! window->Window.FBConfig )
    {
        /*
         * The "fgChooseFBConfig" returned a null meaning that the visual
         * context is not available.
         * Try a couple of variations to see if they will work.
         */
        if( !( fgState.DisplayMode & GLUT_DOUBLE ) )
        {
            fgState.DisplayMode |= GLUT_DOUBLE ;
            window->Window.FBConfig = fgChooseFBConfig( );
            fgState.DisplayMode &= ~GLUT_DOUBLE;
        }

        if( fgState.DisplayMode & GLUT_MULTISAMPLE )
        {
            fgState.DisplayMode &= ~GLUT_MULTISAMPLE ;
            window->Window.FBConfig = fgChooseFBConfig( );
            fgState.DisplayMode |= GLUT_MULTISAMPLE;
        }
    }

    FREEGLUT_INTERNAL_ERROR_EXIT( window->Window.FBConfig != NULL,
                                  "FBConfig with necessary capabilities not found", "fgOpenWindow" );

    /*  Get the X visual.  */
    visualInfo = glXGetVisualFromFBConfig( fgDisplay.Display,
                                           *(window->Window.FBConfig) );

    /*
     * XXX HINT: the masks should be updated when adding/removing callbacks.
     * XXX       This might speed up message processing. Is that true?
     * XXX
     * XXX A: Not appreciably, but it WILL make it easier to debug.
     * XXX    Try tracing old GLUT and try tracing freeglut.  Old GLUT
     * XXX    turns off events that it doesn't need and is a whole lot
     * XXX    more pleasant to trace.  (Think mouse-motion!  Tons of
     * XXX    ``bonus'' GUI events stream in.)
     */
    winAttr.event_mask        =
        StructureNotifyMask | SubstructureNotifyMask | ExposureMask |
        ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask |
        VisibilityChangeMask | EnterWindowMask | LeaveWindowMask |
        PointerMotionMask | ButtonMotionMask;
    winAttr.background_pixmap = None;
    winAttr.background_pixel  = 0;
    winAttr.border_pixel      = 0;

    winAttr.colormap = XCreateColormap(
        fgDisplay.Display, fgDisplay.RootWindow,
        visualInfo->visual, AllocNone
    );

    mask = CWBackPixmap | CWBorderPixel | CWColormap | CWEventMask;

    if( window->IsMenu || ( gameMode == GL_TRUE ) )
    {
        winAttr.override_redirect = True;
        mask |= CWOverrideRedirect;
    }

    if( ! positionUse )
        x = y = -1; /* default window position */
    if( ! sizeUse )
        w = h = 300; /* default window size */

    window->Window.Handle = XCreateWindow(
        fgDisplay.Display,
        window->Parent == NULL ? fgDisplay.RootWindow :
        window->Parent->Window.Handle,
        x, y, w, h, 0,
        visualInfo->depth, InputOutput,
        visualInfo->visual, mask,
        &winAttr
    );

    /*
     * The GLX context creation, possibly trying the direct context rendering
     *  or else use the current context if the user has so specified
     */

    if( window->IsMenu )
    {
        /*
         * If there isn't already an OpenGL rendering context for menu
         * windows, make one
         */
        if( !fgStructure.MenuContext )
        {
            fgStructure.MenuContext =
                (SFG_MenuContext *)malloc( sizeof(SFG_MenuContext) );
            fgStructure.MenuContext->MContext = fghCreateNewContext( window );
        }

        /* window->Window.Context = fgStructure.MenuContext->MContext; */
        window->Window.Context = fghCreateNewContext( window );
    }
    else if( fgState.UseCurrentContext )
    {
        window->Window.Context = glXGetCurrentContext( );

        if( ! window->Window.Context )
            window->Window.Context = fghCreateNewContext( window );
    }
    else
        window->Window.Context = fghCreateNewContext( window );

#if !defined( __FreeBSD__ ) && !defined( __NetBSD__ )
    if(  !glXIsDirect( fgDisplay.Display, window->Window.Context ) )
    {
      if( fgState.DirectContext == GLUT_FORCE_DIRECT_CONTEXT )
        fgError( "Unable to force direct context rendering for window '%s'",
                 title );
    }
#endif

    /*
     * XXX Assume the new window is visible by default
     * XXX Is this a  safe assumption?
     */
    window->State.Visible = GL_TRUE;

    sizeHints.flags = 0;
    if ( positionUse )
        sizeHints.flags |= USPosition;
    if ( sizeUse )
        sizeHints.flags |= USSize;

    /*
     * Fill in the size hints values now (the x, y, width and height
     * settings are obsolete, are there any more WMs that support them?)
     * Unless the X servers actually stop supporting these, we should
     * continue to fill them in.  It is *not* our place to tell the user
     * that they should replace a window manager that they like, and which
     * works, just because *we* think that it's not "modern" enough.
     */
    sizeHints.x      = x;
    sizeHints.y      = y;
    sizeHints.width  = w;
    sizeHints.height = h;

    wmHints.flags = StateHint;
    wmHints.initial_state = fgState.ForceIconic ? IconicState : NormalState;
    /* Prepare the window and iconified window names... */
    XStringListToTextProperty( (char **) &title, 1, &textProperty );

    XSetWMProperties(
        fgDisplay.Display,
        window->Window.Handle,
        &textProperty,
        &textProperty,
        0,
        0,
        &sizeHints,
        &wmHints,
        NULL
    );
    XFree( textProperty.value );

    XSetWMProtocols( fgDisplay.Display, window->Window.Handle,
                     &fgDisplay.DeleteWindow, 1 );

    glXMakeContextCurrent(
        fgDisplay.Display,
        window->Window.Handle,
        window->Window.Handle,
        window->Window.Context
    );

    XMapWindow( fgDisplay.Display, window->Window.Handle );

    XFree(visualInfo);

#elif TARGET_HOST_MS_WINDOWS

    WNDCLASS wc;
    DWORD flags;
    DWORD exFlags = 0;
    ATOM atom;
    int WindowStyle = 0;

    /* Grab the window class we have registered on glutInit(): */
    atom = GetClassInfo( fgDisplay.Instance, _T("FREEGLUT"), &wc );
    FREEGLUT_INTERNAL_ERROR_EXIT ( atom, "Window Class Info Not Found",
                                   "fgOpenWindow" );

    if( gameMode )
    {
        FREEGLUT_INTERNAL_ERROR_EXIT ( window->Parent == NULL,
                                       "Game mode being invoked on a subwindow",
                                       "fgOpenWindow" );

        /*
         * Set the window creation flags appropriately to make the window
         * entirely visible:
         */
        flags = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
    }
    else
    {
        int worig = w, horig = h;

#if !defined(_WIN32_WCE)
        if ( ( ! isSubWindow ) && ( ! window->IsMenu ) )
        {
            /*
             * Update the window dimensions, taking account of window
             * decorations.  "freeglut" is to create the window with the
             * outside of its border at (x,y) and with dimensions (w,h).
             */
            w += (GetSystemMetrics( SM_CXSIZEFRAME ) )*2;
            h += (GetSystemMetrics( SM_CYSIZEFRAME ) )*2 +
                GetSystemMetrics( SM_CYCAPTION );
        }
#endif /* defined(_WIN32_WCE) */

        if( ! positionUse )
        {
            x = CW_USEDEFAULT;
            y = CW_USEDEFAULT;
        }
        /* setting State.Width/Height to call resize callback later */
        if( ! sizeUse )
        {
            if( ! window->IsMenu )
            {
                w = CW_USEDEFAULT;
                h = CW_USEDEFAULT;
            }
            else /* fail safe - Windows can make a window of size (0, 0) */
                w = h = 300; /* default window size */
            window->State.Width = window->State.Height = -1;
        }
        else
        {
            window->State.Width = worig;
            window->State.Height = horig;
        }

        /*
         * There's a small difference between creating the top, child and
         * game mode windows
         */
        flags = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;

        if ( window->IsMenu )
        {
            flags |= WS_POPUP;
            exFlags |= WS_EX_TOOLWINDOW;
        }
#if !defined(_WIN32_WCE)
        else if( window->Parent == NULL )
            flags |= WS_OVERLAPPEDWINDOW;
#endif
        else
            flags |= WS_CHILD;
    }

#if defined(_WIN32_WCE)
    {
        wchar_t* wstr = fghWstrFromStr(title);

        window->Window.Handle = CreateWindow(
            _T("FREEGLUT"),
            wstr,
            WS_VISIBLE | WS_POPUP,
            0,0, 240,320,
            NULL,
            NULL,
            fgDisplay.Instance,
            (LPVOID) window
        );

        free(wstr);

        SHFullScreen(window->Window.Handle, SHFS_HIDESTARTICON);
        SHFullScreen(window->Window.Handle, SHFS_HIDESIPBUTTON);
        SHFullScreen(window->Window.Handle, SHFS_HIDETASKBAR);
        MoveWindow(window->Window.Handle, 0, 0, 240, 320, TRUE);
        ShowWindow(window->Window.Handle, SW_SHOW);
        UpdateWindow(window->Window.Handle);
    }
#else
    window->Window.Handle = CreateWindowEx(
        exFlags,
        _T("FREEGLUT"),
        title,
        flags,
        x, y, w, h,
        (HWND) window->Parent == NULL ? NULL : window->Parent->Window.Handle,
        (HMENU) NULL,
        fgDisplay.Instance,
        (LPVOID) window
    );
#endif /* defined(_WIN32_WCE) */

    if( !( window->Window.Handle ) )
        fgError( "Failed to create a window (%s)!", title );

    /* Make a menu window always on top - fix Feature Request 947118 */
    if( window->IsMenu || gameMode )
        SetWindowPos(
                        window->Window.Handle,
                        HWND_TOPMOST,
                        0, 0, 0, 0,
                        SWP_NOMOVE | SWP_NOSIZE
                    );

    /* Hack to remove the caption (title bar) and/or border
     * and all the system menu controls.
     */
    WindowStyle = GetWindowLong(window->Window.Handle, GWL_STYLE);
    if ( fgState.DisplayMode & GLUT_CAPTIONLESS )
    {
        SetWindowLong ( window->Window.Handle, GWL_STYLE,
                        WindowStyle & ~(WS_DLGFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX));
    }
    else if ( fgState.DisplayMode & GLUT_BORDERLESS )
    {
        SetWindowLong ( window->Window.Handle, GWL_STYLE,
                        WindowStyle & ~(WS_BORDER | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX));
    }
/*  SetWindowPos(window->Window.Handle, NULL, 0, 0, 0, 0,
     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED); */


#if defined(_WIN32_WCE)
    ShowWindow( window->Window.Handle, SW_SHOW );
#else
    ShowWindow( window->Window.Handle,
                fgState.ForceIconic ? SW_SHOWMINIMIZED : SW_SHOW );
#endif /* defined(_WIN32_WCE) */

    UpdateWindow( window->Window.Handle );
    ShowCursor( TRUE );  /* XXX Old comments say "hide cursor"! */

#endif

    fgSetWindow( window );

    window->Window.DoubleBuffered =
        ( fgState.DisplayMode & GLUT_DOUBLE ) ? 1 : 0;

    if ( ! window->Window.DoubleBuffered )
    {
        glDrawBuffer ( GL_FRONT );
        glReadBuffer ( GL_FRONT );
    }
}