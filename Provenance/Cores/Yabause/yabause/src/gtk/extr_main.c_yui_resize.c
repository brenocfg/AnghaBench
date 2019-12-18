#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  float guint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_10__ {TYPE_2__* menu; int /*<<< orphan*/  area; } ;
struct TYPE_9__ {float min_aspect; float max_aspect; } ;
struct TYPE_7__ {scalar_t__ height; } ;
struct TYPE_8__ {TYPE_1__ allocation; } ;
typedef  TYPE_3__ GdkGeometry ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_HINT_ASPECT ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 TYPE_4__* YUI_WINDOW (int /*<<< orphan*/ ) ; 
 scalar_t__ g_key_file_get_integer (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_resize (int /*<<< orphan*/ ,float,scalar_t__) ; 
 int /*<<< orphan*/  gtk_window_set_geometry_hints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyfile ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_window_set_fullscreen (TYPE_4__*,int /*<<< orphan*/ ) ; 

void yui_resize(guint width, guint height, gboolean fullscreen) {
	if (width <= 0) width = 320;
	if (height <= 0) height = 224;

	if (g_key_file_get_integer(keyfile, "General", "KeepRatio", 0))
	{
		GdkGeometry geometry;
		geometry.min_aspect = (float) width / height;
		geometry.max_aspect = (float) width / height;
		gtk_window_set_geometry_hints(GTK_WINDOW(yui), YUI_WINDOW(yui)->area, &geometry, GDK_HINT_ASPECT);
	}
	else
	{
		gtk_window_set_geometry_hints(GTK_WINDOW(yui), YUI_WINDOW(yui)->area, NULL, 0);
	}

	gtk_window_resize(GTK_WINDOW(yui), width, height + YUI_WINDOW(yui)->menu->allocation.height);

	yui_window_set_fullscreen(YUI_WINDOW(yui), fullscreen);
}