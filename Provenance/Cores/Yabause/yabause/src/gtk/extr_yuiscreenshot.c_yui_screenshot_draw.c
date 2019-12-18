#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ YuiScreenshot ;
struct TYPE_7__ {int /*<<< orphan*/  pixels_height; int /*<<< orphan*/  pixels_width; int /*<<< orphan*/  pixels_rowstride; scalar_t__ pixels; } ;
struct TYPE_6__ {int /*<<< orphan*/  area; } ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDK_COLORSPACE_RGB ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* YUI_GL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YUI_VIEWER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_flip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gdk_pixbuf_new_from_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* yui ; 
 int /*<<< orphan*/  yui_viewer_draw_pixbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean yui_screenshot_draw(YuiScreenshot * ys) {
	GdkPixbuf * pixbuf, * correct;

	pixbuf = gdk_pixbuf_new_from_data((const guchar *) YUI_GL(yui->area)->pixels, GDK_COLORSPACE_RGB, FALSE, 8,
			YUI_GL(yui->area)->pixels_width, YUI_GL(yui->area)->pixels_height, YUI_GL(yui->area)->pixels_rowstride, NULL, NULL);
	correct = gdk_pixbuf_flip(pixbuf, FALSE);

	yui_viewer_draw_pixbuf(YUI_VIEWER(ys->image), correct, YUI_GL(yui->area)->pixels_width, YUI_GL(yui->area)->pixels_height);

	g_object_unref(pixbuf);
	g_object_unref(correct);

	return TRUE;
}