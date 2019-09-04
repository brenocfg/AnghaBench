#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  display; int /*<<< orphan*/  xwin; } ;
typedef  TYPE_1__ zbar_window_t ;
typedef  int /*<<< orphan*/  black ;
struct TYPE_8__ {int /*<<< orphan*/  pixel; } ;
typedef  TYPE_2__ XColor ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  int /*<<< orphan*/  GC ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  BlackPixel (int /*<<< orphan*/ ,int) ; 
 int DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCreatePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  XCreatePixmapCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDrawPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeGC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int window_hide_cursor (zbar_window_t *w)
{
    /* FIXME this seems lame...there must be a better way */
    Pixmap empty = XCreatePixmap(w->display, w->xwin, 1, 1, 1);
    GC gc = XCreateGC(w->display, empty, 0, NULL);
    XDrawPoint(w->display, empty, gc, 0, 0);
    XColor black;
    memset(&black, 0, sizeof(black));
    int screen = DefaultScreen(w->display);
    black.pixel = BlackPixel(w->display, screen);
    Cursor cursor =
        XCreatePixmapCursor(w->display, empty, empty, &black, &black, 0, 0);
    XDefineCursor(w->display, w->xwin, cursor);
    XFreeCursor(w->display, cursor);
    XFreeGC(w->display, gc);
    XFreePixmap(w->display, empty);
    return(0);
}