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
typedef  int gint ;
struct TYPE_3__ {int /*<<< orphan*/  group; int /*<<< orphan*/  keyfile; int /*<<< orphan*/  options; } ;
typedef  TYPE_1__ YuiResolution ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_COMBO_BOX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_key_file_set_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int gtk_combo_box_get_active (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_resolution_options_changed(GtkWidget * w, YuiResolution * yr) {
	gint active = gtk_combo_box_get_active(GTK_COMBO_BOX(yr->options));
	switch(active) {
		case 0:
			g_key_file_set_integer(yr->keyfile, yr->group, "Fullscreen", 0);
			g_key_file_set_integer(yr->keyfile, yr->group, "KeepRatio", 0);
			break;
		case 1:
			g_key_file_set_integer(yr->keyfile, yr->group, "Fullscreen", 1);
			g_key_file_set_integer(yr->keyfile, yr->group, "KeepRatio", 0);
			break;
		case 2:
			g_key_file_set_integer(yr->keyfile, yr->group, "Fullscreen", 0);
			g_key_file_set_integer(yr->keyfile, yr->group, "KeepRatio", 1);
			break;
	}
}