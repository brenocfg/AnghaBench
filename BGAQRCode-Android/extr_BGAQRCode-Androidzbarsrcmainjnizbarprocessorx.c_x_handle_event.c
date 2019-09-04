#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  xwin; int /*<<< orphan*/  window; int /*<<< orphan*/  display; } ;
typedef  TYPE_5__ zbar_processor_t ;
struct TYPE_17__ {int /*<<< orphan*/  count; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_6__ XExposeEvent ;
struct TYPE_15__ {int /*<<< orphan*/  button; } ;
struct TYPE_13__ {int /*<<< orphan*/ * l; } ;
struct TYPE_14__ {int format; TYPE_2__ data; int /*<<< orphan*/  message_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_18__ {int type; TYPE_4__ xbutton; int /*<<< orphan*/  xkey; TYPE_3__ xclient; TYPE_1__ xconfigure; } ;
typedef  TYPE_7__ XEvent ;
typedef  int KeySym ;

/* Variables and functions */
#define  Button2 137 
#define  Button3 136 
#define  Button4 135 
#define  Button5 134 
#define  ButtonPress 133 
#define  ClientMessage 132 
#define  ConfigureNotify 131 
#define  DestroyNotify 130 
#define  Expose 129 
 int /*<<< orphan*/  IsModifierKey (int) ; 
#define  KeyPress 128 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int XLookupKeysym (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XNextEvent (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int _zbar_processor_handle_input (TYPE_5__*,int) ; 
 int /*<<< orphan*/  _zbar_processor_invalidate (TYPE_5__*) ; 
 int /*<<< orphan*/  _zbar_window_expose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  zbar_window_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zbar_window_redraw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zbar_window_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprintf (int,char*,...) ; 

__attribute__((used)) static inline int x_handle_event (zbar_processor_t *proc)
{
    XEvent ev;
    XNextEvent(proc->display, &ev);

    switch(ev.type) {
    case Expose: {
        /* FIXME ignore when running(?) */
        XExposeEvent *exp = (XExposeEvent*)&ev;
        while(1) {
            assert(ev.type == Expose);
            _zbar_window_expose(proc->window, exp->x, exp->y,
                                exp->width, exp->height);
            if(!exp->count)
                break;
            XNextEvent(proc->display, &ev);
        }
        zbar_window_redraw(proc->window);
        break;
    }

    case ConfigureNotify:
        zprintf(3, "resized to %d x %d\n",
                ev.xconfigure.width, ev.xconfigure.height);
        zbar_window_resize(proc->window,
                           ev.xconfigure.width, ev.xconfigure.height);
        _zbar_processor_invalidate(proc);
        break;

    case ClientMessage:
        if((ev.xclient.message_type ==
            XInternAtom(proc->display, "WM_PROTOCOLS", 0)) &&
           ev.xclient.format == 32 &&
           (ev.xclient.data.l[0] ==
            XInternAtom(proc->display, "WM_DELETE_WINDOW", 0))) {
            zprintf(3, "WM_DELETE_WINDOW\n");
            return(_zbar_processor_handle_input(proc, -1));
        }

    case KeyPress: {
        KeySym key = XLookupKeysym(&ev.xkey, 0);
        if(IsModifierKey(key))
            break;
        if((key & 0xff00) == 0xff00)
            key &= 0x00ff;
        zprintf(16, "KeyPress(%04lx)\n", key);
        /* FIXME this doesn't really work... */
        return(_zbar_processor_handle_input(proc, key & 0xffff));
    }
    case ButtonPress: {
        zprintf(16, "ButtonPress(%d)\n", ev.xbutton.button);
        int idx = 1;
        switch(ev.xbutton.button) {
        case Button2: idx = 2; break;
        case Button3: idx = 3; break;
        case Button4: idx = 4; break;
        case Button5: idx = 5; break;
        }
        return(_zbar_processor_handle_input(proc, idx));
    }

    case DestroyNotify:
        zprintf(16, "DestroyNotify\n");
        zbar_window_attach(proc->window, NULL, 0);
        proc->xwin = 0;
        return(0);

    default:
        /* ignored */;
    }
    return(0);
}