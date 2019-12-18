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
 int /*<<< orphan*/  CHEAT_HANDLER_TYPE_EMU ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 scalar_t__ cheat_manager_get_size () ; 
 int /*<<< orphan*/  cheat_manager_realloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int action_start_cheat_num_passes(unsigned type, const char *label)
{
   if (cheat_manager_get_size())
   {
      bool refresh                = false;
      menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
      cheat_manager_realloc(0, CHEAT_HANDLER_TYPE_EMU);
   }

   return 0;
}