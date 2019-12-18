#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  YuiScsp ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_handler_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  paused_handler ; 
 int /*<<< orphan*/  running_handler ; 
 int /*<<< orphan*/  yui ; 

void yui_scsp_destroy(YuiScsp * scsp) {
	g_signal_handler_disconnect(yui, running_handler);
	g_signal_handler_disconnect(yui, paused_handler);

	gtk_widget_destroy(GTK_WIDGET(scsp));
}