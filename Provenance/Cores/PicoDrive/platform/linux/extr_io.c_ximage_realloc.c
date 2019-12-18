#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Visual ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/ * XCreateImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDestroyImage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XLockDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUnlockDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZPixmap ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int scr_h ; 
 int scr_w ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * ximage ; 
 int /*<<< orphan*/  xlib_display ; 

__attribute__((used)) static void ximage_realloc(Display *display, Visual *visual)
{
	void *xlib_screen;

	XLockDisplay(xlib_display);

	if (ximage != NULL)
		XDestroyImage(ximage);
	ximage = NULL;

	xlib_screen = calloc(scr_w * scr_h, 4);
	if (xlib_screen != NULL)
		ximage = XCreateImage(display, visual, 24, ZPixmap, 0,
				xlib_screen, scr_w, scr_h, 32, 0);
	if (ximage == NULL)
		fprintf(stderr, "failed to alloc ximage\n");

	XUnlockDisplay(xlib_display);
}