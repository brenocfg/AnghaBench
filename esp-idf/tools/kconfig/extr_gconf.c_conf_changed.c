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

/* Variables and functions */
 int conf_get_changed () ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_btn ; 
 int /*<<< orphan*/  save_menu_item ; 

__attribute__((used)) static void conf_changed(void)
{
	bool changed = conf_get_changed();
	gtk_widget_set_sensitive(save_btn, changed);
	gtk_widget_set_sensitive(save_menu_item, changed);
}