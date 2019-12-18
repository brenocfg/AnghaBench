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
typedef  int /*<<< orphan*/  rarch_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_INPUT_BINDS_CTL_BIND_SINGLE ; 
 int /*<<< orphan*/  menu_input_key_bind_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int setting_bind_action_ok(rarch_setting_t *setting, bool wraparound)
{
   (void)wraparound; /* TODO/FIXME - handle this */

   if (!menu_input_key_bind_set_mode(MENU_INPUT_BINDS_CTL_BIND_SINGLE, setting))
      return -1;
   return 0;
}