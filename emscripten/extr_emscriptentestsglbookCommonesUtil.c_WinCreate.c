#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xev ;
struct TYPE_15__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  input; } ;
typedef  TYPE_3__ XWMHints ;
struct TYPE_16__ {int event_mask; void* override_redirect; } ;
typedef  TYPE_4__ XSetWindowAttributes ;
struct TYPE_13__ {int* l; } ;
struct TYPE_14__ {int format; TYPE_1__ data; int /*<<< orphan*/  message_type; scalar_t__ window; } ;
struct TYPE_17__ {TYPE_2__ xclient; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ XEvent ;
typedef  scalar_t__ Window ;
struct TYPE_18__ {scalar_t__ hWnd; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_6__ ESContext ;
typedef  int /*<<< orphan*/  EGLint ;
typedef  scalar_t__ EGLNativeWindowType ;
typedef  int /*<<< orphan*/  EGLConfig ;
typedef  int /*<<< orphan*/  EGLBoolean ;
typedef  int /*<<< orphan*/  Atom ;

/* Variables and functions */
 int /*<<< orphan*/  CWEventMask ; 
 int /*<<< orphan*/  CWOverrideRedirect ; 
 int /*<<< orphan*/  ClientMessage ; 
 int /*<<< orphan*/  CopyFromParent ; 
 scalar_t__ DefaultRootWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EGL_FALSE ; 
 int /*<<< orphan*/  EGL_TRUE ; 
 int ExposureMask ; 
 void* FALSE ; 
 int /*<<< orphan*/  InputHint ; 
 int /*<<< orphan*/  InputOutput ; 
 int KeyPressMask ; 
 int PointerMotionMask ; 
 int /*<<< orphan*/  SubstructureNotifyMask ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XChangeWindowAttributes (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ XCreateWindow (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/  XMapWindow (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSendEvent (int /*<<< orphan*/ *,scalar_t__,void*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  XSetWMHints (int /*<<< orphan*/ *,scalar_t__,TYPE_3__*) ; 
 int /*<<< orphan*/  XStoreName (int /*<<< orphan*/ *,scalar_t__,char const*) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * x_display ; 

EGLBoolean WinCreate(ESContext *esContext, const char *title)
{
    Window root;
    XSetWindowAttributes swa;
    XSetWindowAttributes  xattr;
    Atom wm_state;
    XWMHints hints;
    XEvent xev;
    EGLConfig ecfg;
    EGLint num_config;
    Window win;

    /*
     * X11 native display initialization
     */

    x_display = XOpenDisplay(NULL);
    if ( x_display == NULL )
    {
        return EGL_FALSE;
    }

    root = DefaultRootWindow(x_display);

    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
    win = XCreateWindow(
               x_display, root,
               0, 0, esContext->width, esContext->height, 0,
               CopyFromParent, InputOutput,
               CopyFromParent, CWEventMask,
               &swa );

    xattr.override_redirect = FALSE;
    XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );

    hints.input = TRUE;
    hints.flags = InputHint;
    XSetWMHints(x_display, win, &hints);

    // make the window visible on the screen
    XMapWindow (x_display, win);
    XStoreName (x_display, win, title);

    // get identifiers for the provided atom name strings
    wm_state = XInternAtom (x_display, "_NET_WM_STATE", FALSE);

    memset ( &xev, 0, sizeof(xev) );
    xev.type                 = ClientMessage;
    xev.xclient.window       = win;
    xev.xclient.message_type = wm_state;
    xev.xclient.format       = 32;
    xev.xclient.data.l[0]    = 1;
    xev.xclient.data.l[1]    = FALSE;
    XSendEvent (
       x_display,
       DefaultRootWindow ( x_display ),
       FALSE,
       SubstructureNotifyMask,
       &xev );

    esContext->hWnd = (EGLNativeWindowType) win;
    return EGL_TRUE;
}