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
 int /*<<< orphan*/  DSMG600_PO_GPIO ; 
 int /*<<< orphan*/  IXP4XX_GPIO_HIGH ; 
 int /*<<< orphan*/  IXP4XX_GPIO_OUT ; 
 int /*<<< orphan*/  gpio_line_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_line_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dsmg600_power_off(void)
{
	/* enable the pwr cntl gpio */
	gpio_line_config(DSMG600_PO_GPIO, IXP4XX_GPIO_OUT);

	/* poweroff */
	gpio_line_set(DSMG600_PO_GPIO, IXP4XX_GPIO_HIGH);
}