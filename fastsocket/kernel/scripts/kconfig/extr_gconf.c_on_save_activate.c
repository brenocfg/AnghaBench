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
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ conf_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  text_insert_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void on_save_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	if (conf_write(NULL))
		text_insert_msg(_("Error"), _("Unable to save configuration !"));
}