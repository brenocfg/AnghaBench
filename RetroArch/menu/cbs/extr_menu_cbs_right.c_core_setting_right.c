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
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 int /*<<< orphan*/  RARCH_CTL_CORE_OPTION_NEXT ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,unsigned int*) ; 

int core_setting_right(unsigned type, const char *label,
      bool wraparound)
{
   unsigned idx     = type - MENU_SETTINGS_CORE_OPTION_START;

   rarch_ctl(RARCH_CTL_CORE_OPTION_NEXT, &idx);

   return 0;
}