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
typedef  int /*<<< orphan*/  core_option_manager_t ;

/* Variables and functions */
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 int /*<<< orphan*/  RARCH_CTL_CORE_OPTIONS_LIST_GET ; 
 int /*<<< orphan*/  core_option_manager_set_default (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int action_start_core_setting(unsigned type,
      const char *label)
{
   unsigned idx                = type - MENU_SETTINGS_CORE_OPTION_START;
   core_option_manager_t *coreopts = NULL;

   if (rarch_ctl(RARCH_CTL_CORE_OPTIONS_LIST_GET, &coreopts))
      core_option_manager_set_default(coreopts, idx);

   return 0;
}