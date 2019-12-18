#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int w; int h; scalar_t__ pixbuf; } ;
typedef  TYPE_1__ YuiViewer ;
struct TYPE_7__ {int /*<<< orphan*/  window; } ;
typedef  int /*<<< orphan*/  GdkPixbuf ;

/* Variables and functions */
 TYPE_3__* GTK_WIDGET (TYPE_1__*) ; 
 scalar_t__ g_object_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (scalar_t__) ; 
 int /*<<< orphan*/  gdk_window_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_queue_draw_area (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void yui_viewer_draw_pixbuf(YuiViewer * yv, GdkPixbuf * pixbuf, int w, int h) {
	if (yv->pixbuf) {
		g_object_unref(yv->pixbuf);
	}
	yv->pixbuf = g_object_ref(pixbuf);
	yv->w = w;
	yv->h = h;
	gdk_window_clear(GTK_WIDGET(yv)->window);
	gtk_widget_queue_draw_area(GTK_WIDGET(yv), 0, 0, w, h);
}