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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  g_signal_emit_by_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void yui_sh_button_bp_add(GtkWidget * widget, gpointer user_data) {
	g_signal_emit_by_name(user_data, "activate");
}