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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  action_group; } ;
typedef  TYPE_1__ YuiWindow ;
typedef  int /*<<< orphan*/  GtkAction ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_ACTION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_action_group_get_action (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_toggle_action_set_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void yui_window_set_frameskip(YuiWindow * yui, gboolean f) {
	GtkAction * action = gtk_action_group_get_action(yui->action_group, "frameskip");
	gtk_toggle_action_set_active(GTK_TOGGLE_ACTION(action), f);
}