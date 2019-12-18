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
typedef  int /*<<< orphan*/  YuiCheckButton ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_check_button_get_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_enable_fixed_base_time(YuiCheckButton *clocksync, YuiCheckButton *fixedbasetime) {
	gtk_widget_set_sensitive(GTK_WIDGET(fixedbasetime),
	                         yui_check_button_get_active(clocksync));
}