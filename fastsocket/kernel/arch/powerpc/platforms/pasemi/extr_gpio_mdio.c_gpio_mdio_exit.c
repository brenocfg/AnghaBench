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
 int /*<<< orphan*/  gpio_mdio_driver ; 
 scalar_t__ gpio_regs ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  of_unregister_platform_driver (int /*<<< orphan*/ *) ; 

void gpio_mdio_exit(void)
{
	of_unregister_platform_driver(&gpio_mdio_driver);
	if (gpio_regs)
		iounmap(gpio_regs);
}