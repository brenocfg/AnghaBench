#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int state; int /*<<< orphan*/  hbox; int /*<<< orphan*/  action_group; } ;
typedef  TYPE_1__ YuiWindow ;
typedef  TYPE_1__ YuiScsp ;
typedef  TYPE_1__ GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BOX (int /*<<< orphan*/ ) ; 
 TYPE_1__* GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 int YUI_IS_INIT ; 
 int YUI_IS_RUNNING ; 
 TYPE_1__* YUI_SCSP (TYPE_1__*) ; 
 TYPE_1__* g_object_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* g_signal_connect_swapped (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_action_connect_proxy (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_action_group_get_action (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_box_pack_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* gtk_button_new () ; 
 TYPE_1__* gtk_button_new_from_stock (char*) ; 
 int /*<<< orphan*/  gtk_widget_show_all (TYPE_1__*) ; 
 void* paused_handler ; 
 void* running_handler ; 
 TYPE_1__* yui ; 
 int /*<<< orphan*/  yui_scsp_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  yui_scsp_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  yui_scsp_get_type () ; 
 int /*<<< orphan*/  yui_scsp_update (TYPE_1__*) ; 

GtkWidget * yui_scsp_new(YuiWindow * y) {
	GtkWidget * dialog;
	YuiScsp * yv;

	yui = y;

	dialog = GTK_WIDGET(g_object_new(yui_scsp_get_type(), NULL));
	yv = YUI_SCSP(dialog);

	{
		GtkWidget * but2, * but3, * but4;
		but2 = gtk_button_new();
		gtk_action_connect_proxy(gtk_action_group_get_action(yui->action_group, "run"), but2);
		gtk_box_pack_start(GTK_BOX(yv->hbox), but2, FALSE, FALSE, 2);

		but3 = gtk_button_new();
		gtk_action_connect_proxy(gtk_action_group_get_action(yui->action_group, "pause"), but3);
		gtk_box_pack_start(GTK_BOX(yv->hbox), but3, FALSE, FALSE, 2);

		but4 = gtk_button_new_from_stock("gtk-close");
		g_signal_connect_swapped(but4, "clicked", G_CALLBACK(yui_scsp_destroy), dialog);
		gtk_box_pack_start(GTK_BOX(yv->hbox), but4, FALSE, FALSE, 2);
	}
	paused_handler = g_signal_connect_swapped(yui, "paused", G_CALLBACK(yui_scsp_update), yv);
	running_handler = g_signal_connect_swapped(yui, "running", G_CALLBACK(yui_scsp_clear), yv);

	if ((yui->state & (YUI_IS_RUNNING | YUI_IS_INIT)) == YUI_IS_INIT)
		yui_scsp_update(yv);

	gtk_widget_show_all(GTK_WIDGET(yv));

	return dialog;
}