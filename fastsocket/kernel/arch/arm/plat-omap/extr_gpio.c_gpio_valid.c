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
 scalar_t__ OMAP_GPIO_IS_MPUIO (int) ; 
 int OMAP_MAX_GPIO_LINES ; 
 scalar_t__ cpu_class_is_omap1 () ; 
 scalar_t__ cpu_is_omap15xx () ; 
 scalar_t__ cpu_is_omap16xx () ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 scalar_t__ cpu_is_omap44xx () ; 
 scalar_t__ cpu_is_omap7xx () ; 

__attribute__((used)) static inline int gpio_valid(int gpio)
{
	if (gpio < 0)
		return -1;
	if (cpu_class_is_omap1() && OMAP_GPIO_IS_MPUIO(gpio)) {
		if (gpio >= OMAP_MAX_GPIO_LINES + 16)
			return -1;
		return 0;
	}
	if (cpu_is_omap15xx() && gpio < 16)
		return 0;
	if ((cpu_is_omap16xx()) && gpio < 64)
		return 0;
	if (cpu_is_omap7xx() && gpio < 192)
		return 0;
	if (cpu_is_omap24xx() && gpio < 128)
		return 0;
	if ((cpu_is_omap34xx() || cpu_is_omap44xx()) && gpio < 192)
		return 0;
	return -1;
}