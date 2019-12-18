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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EP93XX_GPIO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int* gpio_int_enabled ; 
 int* gpio_int_type1 ; 
 int* gpio_int_type2 ; 
 int* gpio_int_unmasked ; 
 int /*<<< orphan*/ * int_en_register_offset ; 
 int /*<<< orphan*/ * int_type1_register_offset ; 
 int /*<<< orphan*/ * int_type2_register_offset ; 

void ep93xx_gpio_update_int_params(unsigned port)
{
	BUG_ON(port > 2);

	__raw_writeb(0, EP93XX_GPIO_REG(int_en_register_offset[port]));

	__raw_writeb(gpio_int_type2[port],
		EP93XX_GPIO_REG(int_type2_register_offset[port]));

	__raw_writeb(gpio_int_type1[port],
		EP93XX_GPIO_REG(int_type1_register_offset[port]));

	__raw_writeb(gpio_int_unmasked[port] & gpio_int_enabled[port],
		EP93XX_GPIO_REG(int_en_register_offset[port]));
}