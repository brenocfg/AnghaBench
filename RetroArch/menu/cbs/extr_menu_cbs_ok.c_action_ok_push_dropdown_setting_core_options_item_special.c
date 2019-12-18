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
 int /*<<< orphan*/  RARCH_CTL_CORE_OPTIONS_LIST_GET ; 
 int action_cancel_pop_default (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  core_option_manager_set_val (int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int action_ok_push_dropdown_setting_core_options_item_special(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   core_option_manager_t *coreopts = NULL;
   int core_option_idx             = (int)atoi(label);

   rarch_ctl(RARCH_CTL_CORE_OPTIONS_LIST_GET, &coreopts);

   if (!coreopts)
      return -1;

   core_option_manager_set_val(coreopts, core_option_idx, idx);
   return action_cancel_pop_default(NULL, NULL, 0, 0);
}