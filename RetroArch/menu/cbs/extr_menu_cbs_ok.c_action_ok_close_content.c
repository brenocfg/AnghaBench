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
 int /*<<< orphan*/  CMD_EVENT_UNLOAD_CORE ; 
 int generic_action_ok_command (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_navigation_set_selection (int /*<<< orphan*/ ) ; 

int action_ok_close_content(const char *path, const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   /* This line resets the navigation pointer so the active entry will be "Run" */
   menu_navigation_set_selection(0);
   return generic_action_ok_command(CMD_EVENT_UNLOAD_CORE);
}