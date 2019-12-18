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
 int /*<<< orphan*/  CMD_EVENT_AUTOSAVE_INIT ; 
 int /*<<< orphan*/  MSG_SRAM_WILL_NOT_BE_SAVED ; 
 int /*<<< orphan*/  RARCH_CTL_IS_SRAM_SAVE_DISABLED ; 
 int /*<<< orphan*/  RARCH_CTL_IS_SRAM_USED ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rarch_use_sram ; 

void path_init_savefile(void)
{
   bool should_sram_be_used = rarch_ctl(RARCH_CTL_IS_SRAM_USED, NULL)
      && !rarch_ctl(RARCH_CTL_IS_SRAM_SAVE_DISABLED, NULL);

   rarch_use_sram    = should_sram_be_used;

   if (!rarch_ctl(RARCH_CTL_IS_SRAM_USED, NULL))
   {
      RARCH_LOG("%s\n",
            msg_hash_to_str(MSG_SRAM_WILL_NOT_BE_SAVED));
      return;
   }

   command_event(CMD_EVENT_AUTOSAVE_INIT, NULL);
}