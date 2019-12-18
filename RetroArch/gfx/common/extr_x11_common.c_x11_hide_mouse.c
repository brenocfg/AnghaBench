#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pixel; } ;
typedef  TYPE_1__ XColor ;
typedef  int /*<<< orphan*/  Window ;
typedef  scalar_t__ Pixmap ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  Cursor ;
typedef  int /*<<< orphan*/  Colormap ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultColormap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ *) ; 
 scalar_t__ None ; 
 int /*<<< orphan*/  XAllocNamedColor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ XCreateBitmapFromData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  XCreatePixmapCursor (int /*<<< orphan*/ *,scalar_t__,scalar_t__,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeColors (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreeCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFreePixmap (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void x11_hide_mouse(Display *dpy, Window win)
{
   static char bm_no_data[] = {0, 0, 0, 0, 0, 0, 0, 0};
   Cursor no_ptr;
   Pixmap bm_no;
   XColor black, dummy;
   Colormap colormap = DefaultColormap(dpy, DefaultScreen(dpy));

   if (!XAllocNamedColor(dpy, colormap, "black", &black, &dummy))
      return;

   bm_no  = XCreateBitmapFromData(dpy, win, bm_no_data, 8, 8);
   no_ptr = XCreatePixmapCursor(dpy, bm_no, bm_no, &black, &black, 0, 0);

   XDefineCursor(dpy, win, no_ptr);
   XFreeCursor(dpy, no_ptr);

   if (bm_no != None)
      XFreePixmap(dpy, bm_no);

   XFreeColors(dpy, colormap, &black.pixel, 1, 0);
}