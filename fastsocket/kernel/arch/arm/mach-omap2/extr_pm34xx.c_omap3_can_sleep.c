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
 scalar_t__ omap3_fclks_active () ; 
 int /*<<< orphan*/  omap_uart_can_sleep () ; 

__attribute__((used)) static int omap3_can_sleep(void)
{
	if (!omap_uart_can_sleep())
		return 0;
	if (omap3_fclks_active())
		return 0;
	return 1;
}