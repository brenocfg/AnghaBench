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
struct TYPE_4__ {int /*<<< orphan*/  running_handler; int /*<<< orphan*/  yui; int /*<<< orphan*/  paused_handler; } ;
typedef  TYPE_1__ YuiVdp2 ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  g_signal_handler_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 

void yui_vdp2_destroy(YuiVdp2 * vdp2) {
	g_signal_handler_disconnect(vdp2->yui, vdp2->paused_handler);
	g_signal_handler_disconnect(vdp2->yui, vdp2->running_handler);
	gtk_widget_destroy(GTK_WIDGET(vdp2));
}