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
 int GPIO_MAP_W ; 
 int GPIO_MAP_X ; 
 int GPIO_MAP_Y ; 
 int GPIO_MAP_Z ; 
 int geode_get_dev_base (int /*<<< orphan*/ ) ; 
 int inl (int) ; 
 int /*<<< orphan*/  outl (int,int) ; 

void geode_gpio_setup_event(unsigned int gpio, int pair, int pme)
{
	u32 base = geode_get_dev_base(GEODE_DEV_GPIO);
	u32 offset, shift, val;

	if (gpio >= 24)
		offset = GPIO_MAP_W;
	else if (gpio >= 16)
		offset = GPIO_MAP_Z;
	else if (gpio >= 8)
		offset = GPIO_MAP_Y;
	else
		offset = GPIO_MAP_X;

	shift = (gpio % 8) * 4;

	val = inl(base + offset);

	/* Clear whatever was there before */
	val &= ~(0xF << shift);

	/* And set the new value */

	val |= ((pair & 7) << shift);

	/* Set the PME bit if this is a PME event */

	if (pme)
		val |= (1 << (shift + 3));

	outl(val, base + offset);
}