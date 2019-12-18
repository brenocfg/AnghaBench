#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  action_group; } ;
typedef  TYPE_1__ YuiWindow ;
typedef  int /*<<< orphan*/  GtkToggleAction ;
typedef  int /*<<< orphan*/  GtkAction ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_ACTION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ToggleNBG0 ; 
 int /*<<< orphan*/  ToggleNBG1 ; 
 int /*<<< orphan*/  ToggleNBG2 ; 
 int /*<<< orphan*/  ToggleNBG3 ; 
 int /*<<< orphan*/  ToggleRBG0 ; 
 int /*<<< orphan*/  ToggleVDP1 ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_signal_connect_swapped (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_action_group_add_action_with_accel (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gtk_action_new (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_main_quit ; 
 int /*<<< orphan*/ * gtk_toggle_action_new (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_toggle_action_set_active (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_window_pause ; 
 int /*<<< orphan*/  yui_window_reset ; 
 int /*<<< orphan*/  yui_window_run ; 
 int /*<<< orphan*/  yui_window_toggle_frameskip ; 
 int /*<<< orphan*/  yui_window_toggle_fullscreen ; 

__attribute__((used)) static void yui_window_create_actions(YuiWindow * yw) {
	GtkAction * action;
	GtkToggleAction * taction;

	action = gtk_action_new("run", _("Run"), _("start emulation"), "gtk-media-play");
	gtk_action_group_add_action_with_accel(yw->action_group, action, "<Ctrl>r");
	g_signal_connect_swapped(action, "activate", G_CALLBACK(yui_window_run), yw);

	action = gtk_action_new("pause", _("Pause"), _("pause emulation"), "gtk-media-pause");
	gtk_action_group_add_action_with_accel(yw->action_group, action, "<Ctrl>p");
	g_signal_connect_swapped(action, "activate", G_CALLBACK(yui_window_pause), yw);

	action = gtk_action_new("reset", _("Reset"), _("reset emulation"), NULL);
	gtk_action_group_add_action_with_accel(yw->action_group, action, NULL);
	g_signal_connect_swapped(action, "activate", G_CALLBACK(yui_window_reset), yw);

	taction = gtk_toggle_action_new("fullscreen", _("Fullscreen"), NULL, "gtk-fullscreen");
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), "<Ctrl>f");
	g_signal_connect(taction, "activate", G_CALLBACK(yui_window_toggle_fullscreen), yw);

	taction = gtk_toggle_action_new("frameskip", _("Frame Skip/Limiter"), NULL, NULL);
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), NULL);
	g_signal_connect(taction, "activate", G_CALLBACK(yui_window_toggle_frameskip), yw);

	action = gtk_action_new("quit", _("Quit"), NULL, "gtk-quit");
	gtk_action_group_add_action_with_accel(yw->action_group, action, "<Ctrl>q");
	g_signal_connect(action, "activate", G_CALLBACK(gtk_main_quit), yw);

	taction = gtk_toggle_action_new("toggle_vdp1", _("VDP1"), NULL, NULL);
	gtk_toggle_action_set_active(taction, TRUE);
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), NULL);
	g_signal_connect(taction, "activate", G_CALLBACK(ToggleVDP1), NULL);

	taction = gtk_toggle_action_new("toggle_nbg0", _("NBG0"), NULL, NULL);
	gtk_toggle_action_set_active(taction, TRUE);
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), NULL);
	g_signal_connect(taction, "activate", G_CALLBACK(ToggleNBG0), NULL);

	taction = gtk_toggle_action_new("toggle_nbg1", _("NBG1"), NULL, NULL);
	gtk_toggle_action_set_active(taction, TRUE);
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), NULL);
	g_signal_connect(taction, "activate", G_CALLBACK(ToggleNBG1), NULL);

	taction = gtk_toggle_action_new("toggle_nbg2", _("NBG2"), NULL, NULL);
	gtk_toggle_action_set_active(taction, TRUE);
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), NULL);
	g_signal_connect(taction, "activate", G_CALLBACK(ToggleNBG2), NULL);

	taction = gtk_toggle_action_new("toggle_nbg3", _("NBG3"), NULL, NULL);
	gtk_toggle_action_set_active(taction, TRUE);
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), NULL);
	g_signal_connect(taction, "activate", G_CALLBACK(ToggleNBG3), NULL);

	taction = gtk_toggle_action_new("toggle_rbg0", _("RBG0"), NULL, NULL);
	gtk_toggle_action_set_active(taction, TRUE);
	gtk_action_group_add_action_with_accel(yw->action_group, GTK_ACTION(taction), NULL);
	g_signal_connect(taction, "activate", G_CALLBACK(ToggleRBG0), NULL);
}