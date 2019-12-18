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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  YuiCheckButton ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TOGGLE_BUTTON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_toggle_button_get_active (int /*<<< orphan*/ ) ; 

gboolean yui_check_button_get_active(YuiCheckButton * ycb) {
	return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ycb));
}