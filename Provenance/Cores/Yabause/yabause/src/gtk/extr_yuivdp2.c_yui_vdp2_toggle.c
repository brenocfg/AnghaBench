#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_5__ {TYPE_1__* yui; } ;
typedef  TYPE_2__ YuiVdp2 ;
struct TYPE_4__ {int /*<<< orphan*/  action_group; } ;
typedef  int /*<<< orphan*/  GtkCellRendererToggle ;
typedef  int /*<<< orphan*/  GtkAction ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_ACTION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_action_group_get_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_action_get_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_toggle_action_set_active (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/  const*,char*,int*) ; 
 int /*<<< orphan*/ * yui_vdp2_action_names ; 

__attribute__((used)) static void yui_vdp2_toggle(GtkCellRendererToggle * crt, const gchar * path, YuiVdp2 * yv) {
	int val;
	GtkAction * action = NULL;

	sscanf(path, "%d", &val);
	if (! yui_vdp2_action_names[val]) return;

	action = gtk_action_group_get_action(yv->yui->action_group, yui_vdp2_action_names[val]);
	gtk_toggle_action_set_active(GTK_TOGGLE_ACTION(action), ! gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(action)));
}