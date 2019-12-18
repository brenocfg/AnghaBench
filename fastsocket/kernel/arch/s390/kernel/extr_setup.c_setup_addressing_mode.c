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
 scalar_t__ PRIMARY_SPACE_MODE ; 
 int /*<<< orphan*/  PSW32_ASC_PRIMARY ; 
 int /*<<< orphan*/  PSW32_ASC_SECONDARY ; 
 int /*<<< orphan*/  PSW_ASC_PRIMARY ; 
 int /*<<< orphan*/  PSW_ASC_SECONDARY ; 
 scalar_t__ SECONDARY_SPACE_MODE ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ set_amode_and_uaccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ user_mode ; 

__attribute__((used)) static void setup_addressing_mode(void)
{
	if (user_mode == SECONDARY_SPACE_MODE) {
		if (set_amode_and_uaccess(PSW_ASC_SECONDARY,
					  PSW32_ASC_SECONDARY))
			pr_info("Execute protection active, "
				"mvcos available\n");
		else
			pr_info("Execute protection active, "
				"mvcos not available\n");
	} else if (user_mode == PRIMARY_SPACE_MODE) {
		if (set_amode_and_uaccess(PSW_ASC_PRIMARY, PSW32_ASC_PRIMARY))
			pr_info("Address spaces switched, "
				"mvcos available\n");
		else
			pr_info("Address spaces switched, "
				"mvcos not available\n");
	}
}