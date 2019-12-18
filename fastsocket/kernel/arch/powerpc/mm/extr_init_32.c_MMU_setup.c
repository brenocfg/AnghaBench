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
 int __map_without_bats ; 
 int __map_without_ltlbs ; 
 int /*<<< orphan*/  cmd_line ; 
 scalar_t__ strstr (int /*<<< orphan*/ ,char*) ; 

void MMU_setup(void)
{
	/* Check for nobats option (used in mapin_ram). */
	if (strstr(cmd_line, "nobats")) {
		__map_without_bats = 1;
	}

	if (strstr(cmd_line, "noltlbs")) {
		__map_without_ltlbs = 1;
	}
#ifdef CONFIG_DEBUG_PAGEALLOC
	__map_without_bats = 1;
	__map_without_ltlbs = 1;
#endif
}