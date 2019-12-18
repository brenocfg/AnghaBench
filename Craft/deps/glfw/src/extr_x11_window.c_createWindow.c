#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_18__ ;
typedef  struct TYPE_30__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  hints ;
struct TYPE_35__ {scalar_t__ title; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  resizable; scalar_t__ monitor; scalar_t__ floating; int /*<<< orphan*/  decorated; } ;
typedef  TYPE_4__ _GLFWwndconfig ;
struct TYPE_33__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  ypos; int /*<<< orphan*/  xpos; int /*<<< orphan*/  handle; int /*<<< orphan*/  ic; int /*<<< orphan*/  colormap; } ;
struct TYPE_36__ {TYPE_2__ x11; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_37__ {int flags; char* res_name; char* res_class; int /*<<< orphan*/  max_height; int /*<<< orphan*/  min_height; int /*<<< orphan*/  max_width; int /*<<< orphan*/  min_width; scalar_t__ y; scalar_t__ x; int /*<<< orphan*/  initial_state; } ;
typedef  TYPE_6__ XWMHints ;
struct TYPE_38__ {int /*<<< orphan*/  visual; int /*<<< orphan*/  depth; } ;
typedef  TYPE_7__ XVisualInfo ;
typedef  TYPE_6__ XSizeHints ;
struct TYPE_39__ {int event_mask; int /*<<< orphan*/  override_redirect; scalar_t__ border_pixel; int /*<<< orphan*/  colormap; } ;
typedef  TYPE_9__ XSetWindowAttributes ;
typedef  int /*<<< orphan*/  XPointer ;
struct TYPE_30__ {int deviceid; int mask_len; unsigned char* mask; } ;
typedef  TYPE_10__ XIEventMask ;
typedef  TYPE_6__ XClassHint ;
struct TYPE_32__ {scalar_t__ available; } ;
struct TYPE_34__ {int WM_DELETE_WINDOW; int NET_WM_PING; scalar_t__ im; int /*<<< orphan*/  display; scalar_t__ XdndAware; TYPE_1__ xi; scalar_t__ NET_WM_PID; scalar_t__ NET_WM_STATE_ABOVE; scalar_t__ NET_WM_STATE; scalar_t__ MOTIF_WM_HINTS; int /*<<< orphan*/  NET_WM_STATE_FULLSCREEN; int /*<<< orphan*/  context; int /*<<< orphan*/  root; } ;
struct TYPE_31__ {TYPE_3__ x11; } ;
typedef  int /*<<< orphan*/  GLboolean ;
typedef  int Atom ;

/* Variables and functions */
 int /*<<< orphan*/  AllocNone ; 
 int ButtonPressMask ; 
 int ButtonReleaseMask ; 
 unsigned long CWBorderPixel ; 
 unsigned long CWColormap ; 
 unsigned long CWEventMask ; 
 int /*<<< orphan*/  CWOverrideRedirect ; 
 int EnterWindowMask ; 
 int ExposureMask ; 
 int FocusChangeMask ; 
 int /*<<< orphan*/  GLFW_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  InputOutput ; 
 int KeyPressMask ; 
 int KeyReleaseMask ; 
 int LeaveWindowMask ; 
 int /*<<< orphan*/  NormalState ; 
 int PMaxSize ; 
 int PMinSize ; 
 int PPosition ; 
 int PointerMotionMask ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int PropertyChangeMask ; 
 int /*<<< orphan*/  RRScreenChangeNotifyMask ; 
 int StateHint ; 
 int StructureNotifyMask ; 
 int /*<<< orphan*/  True ; 
 int VisibilityChangeMask ; 
 scalar_t__ XA_ATOM ; 
 scalar_t__ XA_CARDINAL ; 
 TYPE_6__* XAllocClassHint () ; 
 TYPE_6__* XAllocSizeHints () ; 
 TYPE_6__* XAllocWMHints () ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XChangeWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  XCreateColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateIC (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,TYPE_9__*) ; 
 int /*<<< orphan*/  XFree (TYPE_6__*) ; 
 int XIMPreeditNothing ; 
 int XIMStatusNothing ; 
 int /*<<< orphan*/  XISelectEvents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_10__*,int) ; 
 int /*<<< orphan*/  XISetMask (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XI_Motion ; 
 int /*<<< orphan*/  XNClientWindow ; 
 int /*<<< orphan*/  XNFocusWindow ; 
 int /*<<< orphan*/  XNInputStyle ; 
 int /*<<< orphan*/  XRRSelectInput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSaveContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetClassHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  XSetWMHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  XSetWMNormalHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  XSetWMProtocols (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 TYPE_7__* _GLFW_X11_CONTEXT_VISUAL ; 
 int /*<<< orphan*/  _NET_WM_STATE_ADD ; 
 TYPE_18__ _glfw ; 
 int /*<<< orphan*/  _glfwGrabXErrorHandler () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwInputXError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwPlatformGetMonitorPos (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowPos (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowSize (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowTitle (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  _glfwReleaseXErrorHandler () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  sendEventToWM (TYPE_5__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static GLboolean createWindow(_GLFWwindow* window,
                              const _GLFWwndconfig* wndconfig)
{
    unsigned long wamask;
    XSetWindowAttributes wa;
    XVisualInfo* vi = _GLFW_X11_CONTEXT_VISUAL;

    // Every window needs a colormap
    // Create one based on the visual used by the current context
    // TODO: Decouple this from context creation

    window->x11.colormap = XCreateColormap(_glfw.x11.display,
                                           _glfw.x11.root,
                                           vi->visual,
                                           AllocNone);

    // Create the actual window
    {
        wamask = CWBorderPixel | CWColormap | CWEventMask;

        wa.colormap = window->x11.colormap;
        wa.border_pixel = 0;
        wa.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask |
                        PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                        ExposureMask | FocusChangeMask | VisibilityChangeMask |
                        EnterWindowMask | LeaveWindowMask | PropertyChangeMask;

        _glfwGrabXErrorHandler();

        window->x11.handle = XCreateWindow(_glfw.x11.display,
                                           _glfw.x11.root,
                                           0, 0,
                                           wndconfig->width, wndconfig->height,
                                           0,          // Border width
                                           vi->depth,  // Color depth
                                           InputOutput,
                                           vi->visual,
                                           wamask,
                                           &wa);

        _glfwReleaseXErrorHandler();

        if (!window->x11.handle)
        {
            _glfwInputXError(GLFW_PLATFORM_ERROR,
                             "X11: Failed to create window");
            return GL_FALSE;
        }

        XSaveContext(_glfw.x11.display,
                     window->x11.handle,
                     _glfw.x11.context,
                     (XPointer) window);
    }

    if (wndconfig->monitor)
    {
        if (!_glfw.x11.NET_WM_STATE || !_glfw.x11.NET_WM_STATE_FULLSCREEN)
        {
            // This is the butcher's way of removing window decorations
            // Setting the override-redirect attribute on a window makes the
            // window manager ignore the window completely (ICCCM, section 4)
            // The good thing is that this makes undecorated full screen windows
            // easy to do; the bad thing is that we have to do everything
            // manually and some things (like iconify/restore) won't work at
            // all, as those are tasks usually performed by the window manager

            XSetWindowAttributes attributes;
            attributes.override_redirect = True;
            XChangeWindowAttributes(_glfw.x11.display,
                                    window->x11.handle,
                                    CWOverrideRedirect,
                                    &attributes);
        }
    }
    else
    {
        if (!wndconfig->decorated)
        {
            struct
            {
                unsigned long flags;
                unsigned long functions;
                unsigned long decorations;
                long input_mode;
                unsigned long status;
            } hints;

            hints.flags = 2;       // Set decorations
            hints.decorations = 0; // No decorations

            XChangeProperty(_glfw.x11.display, window->x11.handle,
                            _glfw.x11.MOTIF_WM_HINTS,
                            _glfw.x11.MOTIF_WM_HINTS, 32,
                            PropModeReplace,
                            (unsigned char*) &hints,
                            sizeof(hints) / sizeof(long));
        }

        if (wndconfig->floating)
        {
            if (_glfw.x11.NET_WM_STATE && _glfw.x11.NET_WM_STATE_ABOVE)
            {
                sendEventToWM(window,
                              _glfw.x11.NET_WM_STATE,
                              _NET_WM_STATE_ADD,
                              _glfw.x11.NET_WM_STATE_ABOVE,
                              0, 1, 0);
            }
        }
    }


    // Declare the WM protocols supported by GLFW
    {
        int count = 0;
        Atom protocols[2];

        // The WM_DELETE_WINDOW ICCCM protocol
        // Basic window close notification protocol
        if (_glfw.x11.WM_DELETE_WINDOW)
            protocols[count++] = _glfw.x11.WM_DELETE_WINDOW;

        // The _NET_WM_PING EWMH protocol
        // Tells the WM to ping the GLFW window and flag the application as
        // unresponsive if the WM doesn't get a reply within a few seconds
        if (_glfw.x11.NET_WM_PING)
            protocols[count++] = _glfw.x11.NET_WM_PING;

        if (count > 0)
        {
            XSetWMProtocols(_glfw.x11.display, window->x11.handle,
                            protocols, count);
        }
    }

    if (_glfw.x11.NET_WM_PID)
    {
        const pid_t pid = getpid();

        XChangeProperty(_glfw.x11.display,  window->x11.handle,
                        _glfw.x11.NET_WM_PID, XA_CARDINAL, 32,
                        PropModeReplace,
                        (unsigned char*) &pid, 1);
    }

    // Set ICCCM WM_HINTS property
    {
        XWMHints* hints = XAllocWMHints();
        if (!hints)
        {
            _glfwInputError(GLFW_OUT_OF_MEMORY,
                            "X11: Failed to allocate WM hints");
            return GL_FALSE;
        }

        hints->flags = StateHint;
        hints->initial_state = NormalState;

        XSetWMHints(_glfw.x11.display, window->x11.handle, hints);
        XFree(hints);
    }

    // Set ICCCM WM_NORMAL_HINTS property (even if no parts are set)
    {
        XSizeHints* hints = XAllocSizeHints();
        hints->flags = 0;

        if (wndconfig->monitor)
        {
            hints->flags |= PPosition;
            _glfwPlatformGetMonitorPos(wndconfig->monitor, &hints->x, &hints->y);
        }
        else
        {
            // HACK: Explicitly setting PPosition to any value causes some WMs,
            //       notably Compiz and Metacity, to honor the position of
            //       unmapped windows set by XMoveWindow
            hints->flags |= PPosition;
            hints->x = hints->y = 0;
        }

        if (!wndconfig->resizable)
        {
            hints->flags |= (PMinSize | PMaxSize);
            hints->min_width  = hints->max_width  = wndconfig->width;
            hints->min_height = hints->max_height = wndconfig->height;
        }

        XSetWMNormalHints(_glfw.x11.display, window->x11.handle, hints);
        XFree(hints);
    }

    // Set ICCCM WM_CLASS property
    // HACK: Until a mechanism for specifying the application name is added, the
    //       initial window title is used as the window class name
    if (strlen(wndconfig->title))
    {
        XClassHint* hint = XAllocClassHint();
        hint->res_name = (char*) wndconfig->title;
        hint->res_class = (char*) wndconfig->title;

        XSetClassHint(_glfw.x11.display, window->x11.handle, hint);
        XFree(hint);
    }

#if defined(_GLFW_HAS_XINPUT)
    if (_glfw.x11.xi.available)
    {
        // Select for XInput2 events

        XIEventMask eventmask;
        unsigned char mask[] = { 0 };

        eventmask.deviceid = 2;
        eventmask.mask_len = sizeof(mask);
        eventmask.mask = mask;
        XISetMask(mask, XI_Motion);

        XISelectEvents(_glfw.x11.display, window->x11.handle, &eventmask, 1);
    }
#endif /*_GLFW_HAS_XINPUT*/

    if (_glfw.x11.XdndAware)
    {
        // Announce support for Xdnd (drag and drop)
        const Atom version = 5;
        XChangeProperty(_glfw.x11.display, window->x11.handle,
                        _glfw.x11.XdndAware, XA_ATOM, 32,
                        PropModeReplace, (unsigned char*) &version, 1);
    }

    _glfwPlatformSetWindowTitle(window, wndconfig->title);

    XRRSelectInput(_glfw.x11.display, window->x11.handle,
                   RRScreenChangeNotifyMask);

    if (_glfw.x11.im)
    {
        window->x11.ic = XCreateIC(_glfw.x11.im,
                                   XNInputStyle,
                                   XIMPreeditNothing | XIMStatusNothing,
                                   XNClientWindow,
                                   window->x11.handle,
                                   XNFocusWindow,
                                   window->x11.handle,
                                   NULL);
    }

    _glfwPlatformGetWindowPos(window, &window->x11.xpos, &window->x11.ypos);
    _glfwPlatformGetWindowSize(window, &window->x11.width, &window->x11.height);

    return GL_TRUE;
}