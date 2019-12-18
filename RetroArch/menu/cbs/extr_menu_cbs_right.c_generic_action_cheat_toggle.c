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
 int /*<<< orphan*/  cheat_manager_toggle_index (unsigned int) ; 

int generic_action_cheat_toggle(size_t idx, unsigned type, const char *label,
      bool wraparound)
{
   cheat_manager_toggle_index((unsigned)idx);

   return 0;
}