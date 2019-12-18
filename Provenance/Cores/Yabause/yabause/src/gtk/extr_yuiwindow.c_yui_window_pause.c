#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; int /*<<< orphan*/  action_group; int /*<<< orphan*/  area; } ;
typedef  TYPE_1__ YuiWindow ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GINT_TO_POINTER (int) ; 
 int /*<<< orphan*/  G_OBJECT (TYPE_1__*) ; 
 int /*<<< orphan*/  SCSP_MUTE_SYSTEM ; 
 int /*<<< orphan*/  ScspMuteAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  YUI_GL (int /*<<< orphan*/ ) ; 
 int YUI_IS_RUNNING ; 
 size_t YUI_WINDOW_PAUSED_SIGNAL ; 
 int /*<<< orphan*/  g_idle_remove_by_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_signal_emit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_action_group_get_action (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gtk_action_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_gl_dump_screen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * yui_window_signals ; 

void yui_window_pause(YuiWindow * yui) {
	if (yui->state & YUI_IS_RUNNING) {
		yui_gl_dump_screen(YUI_GL(yui->area));
		ScspMuteAudio(SCSP_MUTE_SYSTEM);
		g_idle_remove_by_data(GINT_TO_POINTER(1));
		g_signal_emit(G_OBJECT(yui), yui_window_signals[YUI_WINDOW_PAUSED_SIGNAL], 0);
		yui->state &= ~YUI_IS_RUNNING;
		gtk_action_set_sensitive(gtk_action_group_get_action(yui->action_group, "run"), TRUE);
		gtk_action_set_sensitive(gtk_action_group_get_action(yui->action_group, "pause"), FALSE);
	}
}