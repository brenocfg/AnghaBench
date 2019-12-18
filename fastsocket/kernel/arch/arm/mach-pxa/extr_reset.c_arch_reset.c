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
 int /*<<< orphan*/  RESET_STATUS_ALL ; 
 int /*<<< orphan*/  clear_reset_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_gpio_reset () ; 
 int /*<<< orphan*/  do_hw_reset () ; 

void arch_reset(char mode, const char *cmd)
{
	clear_reset_status(RESET_STATUS_ALL);

	switch (mode) {
	case 's':
		/* Jump into ROM at address 0 */
		cpu_reset(0);
		break;
	case 'g':
		do_gpio_reset();
		break;
	case 'h':
	default:
		do_hw_reset();
		break;
	}
}