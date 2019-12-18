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
struct TYPE_4__ {int /*<<< orphan*/  paused_handler; int /*<<< orphan*/  running_handler; } ;
typedef  TYPE_1__ YuiM68k ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  g_signal_handler_disconnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/ * yui_m68k ; 

void yui_m68k_destroy(YuiM68k * m68k) {
  g_signal_handler_disconnect(yui, m68k->running_handler);
  g_signal_handler_disconnect(yui, m68k->paused_handler);
  
  yui_m68k = NULL;

  gtk_widget_destroy(GTK_WIDGET(m68k));
}