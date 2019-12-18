#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  guchar ;
struct TYPE_3__ {int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ YuiVdp2 ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_COLORSPACE_RGB ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  YUI_VIEWER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gdk_pixbuf_new_from_data (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yui_texture_free ; 
 int /*<<< orphan*/  yui_viewer_draw_pixbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void yui_vdp2_draw(YuiVdp2 * vdp2, u32 * texture, int w, int h) {
	GdkPixbuf * pixbuf;
	int rowstride;

	if ((texture != NULL) && (w > 0) && (h > 0)) {
		rowstride = w * 4;
		rowstride += (rowstride % 4)? (4 - (rowstride % 4)): 0;
		pixbuf = gdk_pixbuf_new_from_data((const guchar *) texture, GDK_COLORSPACE_RGB, TRUE, 8,
			w, h, rowstride, yui_texture_free, NULL);

		yui_viewer_draw_pixbuf(YUI_VIEWER(vdp2->image), pixbuf, w, h);

		g_object_unref(pixbuf);
	}
}