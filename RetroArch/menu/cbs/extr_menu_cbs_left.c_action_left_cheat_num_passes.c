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
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 int cheat_manager_get_size () ; 
 int /*<<< orphan*/  cheat_manager_realloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int action_left_cheat_num_passes(unsigned type, const char *label,
      bool wraparound)
{
   bool refresh      = false;
   unsigned new_size = 0;

   if (cheat_manager_get_size())
      new_size = cheat_manager_get_size() - 1;
   menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
   menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);
   cheat_manager_realloc(new_size, CHEAT_HANDLER_TYPE_EMU);

   return 0;
}