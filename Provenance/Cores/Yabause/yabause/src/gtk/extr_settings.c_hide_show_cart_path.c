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
typedef  int gint ;
typedef  int /*<<< orphan*/  YuiRange ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ ) ; 
 int yui_range_get_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hide_show_cart_path(YuiRange * instance, gpointer data) {
	gint i = yui_range_get_active(instance);

	if (i == 8) {
		gtk_widget_hide(data);
	} else {
		gtk_widget_show(data);
	}
}