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
struct gpio_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ OMAP_GPIO_IS_MPUIO (int) ; 
 scalar_t__ cpu_is_omap15xx () ; 
 scalar_t__ cpu_is_omap16xx () ; 
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 scalar_t__ cpu_is_omap44xx () ; 
 scalar_t__ cpu_is_omap7xx () ; 
 struct gpio_bank* gpio_bank ; 

__attribute__((used)) static inline struct gpio_bank *get_gpio_bank(int gpio)
{
	if (cpu_is_omap15xx()) {
		if (OMAP_GPIO_IS_MPUIO(gpio))
			return &gpio_bank[0];
		return &gpio_bank[1];
	}
	if (cpu_is_omap16xx()) {
		if (OMAP_GPIO_IS_MPUIO(gpio))
			return &gpio_bank[0];
		return &gpio_bank[1 + (gpio >> 4)];
	}
	if (cpu_is_omap7xx()) {
		if (OMAP_GPIO_IS_MPUIO(gpio))
			return &gpio_bank[0];
		return &gpio_bank[1 + (gpio >> 5)];
	}
	if (cpu_is_omap24xx())
		return &gpio_bank[gpio >> 5];
	if (cpu_is_omap34xx() || cpu_is_omap44xx())
		return &gpio_bank[gpio >> 5];
	BUG();
	return NULL;
}