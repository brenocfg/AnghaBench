#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_15__ {unsigned long xwin; int /*<<< orphan*/ * display; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* state; } ;
typedef  TYPE_1__ zbar_window_t ;
struct TYPE_16__ {TYPE_11__* font; scalar_t__ gc; int /*<<< orphan*/ * exposed; int /*<<< orphan*/ * logo_zbars; } ;
typedef  TYPE_2__ window_state_t ;
struct TYPE_17__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ XWindowAttributes ;
struct TYPE_14__ {int /*<<< orphan*/  fid; } ;

/* Variables and functions */
 scalar_t__ XCreateGC (void*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyRegion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFreeFont (int /*<<< orphan*/ *,TYPE_11__*) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  XGetWindowAttributes (int /*<<< orphan*/ *,unsigned long,TYPE_3__*) ; 
 TYPE_11__* XLoadQueryFont (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetFont (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZBAR_OVERLAY_FONT ; 
 int _zbar_window_probe_ximage (TYPE_1__*) ; 
 int /*<<< orphan*/  _zbar_window_resize (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  window_alloc_colors (TYPE_1__*) ; 
 int /*<<< orphan*/  window_hide_cursor (TYPE_1__*) ; 
 int /*<<< orphan*/  zprintf (int,char*) ; 

int _zbar_window_attach (zbar_window_t *w,
                         void *display,
                         unsigned long win)
{
    window_state_t *x = w->state;
    if(w->display) {
        /* cleanup existing resources */
        if(x->gc)
            XFreeGC(w->display, x->gc);
        assert(!x->exposed);
        if(x->font) {
            XFreeFont(w->display, x->font);
            x->font = NULL;
        }
        if(x->logo_zbars) {
            XDestroyRegion(x->logo_zbars);
            x->logo_zbars = NULL;
        }
        if(x->exposed) {
            XDestroyRegion(x->exposed);
            x->exposed = NULL;
        }
        w->display = NULL;
    }
    w->xwin = 0;

    if(!display || !win) {
        if(x) {
            free(x);
            w->state = NULL;
        }
        return(0);
    }

    if(!x)
        x = w->state = calloc(1, sizeof(window_state_t));

    w->display = display;
    w->xwin = win;
    x->gc = XCreateGC(display, win, 0, NULL);

    XWindowAttributes attr;
    XGetWindowAttributes(w->display, w->xwin, &attr);
    w->width = attr.width;
    w->height = attr.height;
    _zbar_window_resize(w);

    window_alloc_colors(w);
    window_hide_cursor(w);

    /* load overlay font */
    x->font = XLoadQueryFont(w->display, ZBAR_OVERLAY_FONT);
    if(x->font)
        XSetFont(w->display, x->gc, x->font->fid);

    /* FIXME add interface preference override */
#ifdef HAVE_X11_EXTENSIONS_XVLIB_H
    if(!_zbar_window_probe_xv(w))
        return(0);
#endif

    zprintf(1, "falling back to XImage\n");
    return(_zbar_window_probe_ximage(w));
}