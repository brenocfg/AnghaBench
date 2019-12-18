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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GEODE_DEV_GPIO ; 
 int geode_get_dev_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outl (int,int) ; 

void geode_gpio_clear(u32 gpio, unsigned int reg)
{
	u32 base = geode_get_dev_base(GEODE_DEV_GPIO);

	if (!base)
		return;

	/* low bank register */
	if (gpio & 0xFFFF)
		outl((gpio & 0xFFFF) << 16, base + reg);
	/* high bank register */
	gpio &= (0xFFFF << 16);
	if (gpio)
		outl(gpio, base + 0x80 + reg);
}