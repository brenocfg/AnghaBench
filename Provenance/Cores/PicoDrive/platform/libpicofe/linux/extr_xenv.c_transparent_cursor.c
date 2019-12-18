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
struct xstuff {int /*<<< orphan*/  (* pXFreePixmap ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pXCreatePixmapCursor ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* pXCreateBitmapFromData ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ;} ;
typedef  int /*<<< orphan*/  dummy ;
typedef  int /*<<< orphan*/  XColor ;
typedef  int /*<<< orphan*/  Window ;
typedef  int /*<<< orphan*/  Pixmap ;
typedef  int /*<<< orphan*/  Display ;
typedef  int /*<<< orphan*/  Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Cursor transparent_cursor(struct xstuff *xf, Display *display, Window win)
{
	Cursor cursor;
	Pixmap pix;
	XColor dummy;
	char d = 0;

	memset(&dummy, 0, sizeof(dummy));
	pix = xf->pXCreateBitmapFromData(display, win, &d, 1, 1);
	cursor = xf->pXCreatePixmapCursor(display, pix, pix,
			&dummy, &dummy, 0, 0);
	xf->pXFreePixmap(display, pix);
	return cursor;
}