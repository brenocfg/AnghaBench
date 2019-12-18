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
 scalar_t__ cpu_is_omap24xx () ; 
 scalar_t__ cpu_is_omap34xx () ; 
 scalar_t__ cpu_is_omap44xx () ; 
 scalar_t__ cpu_is_omap7xx () ; 

__attribute__((used)) static inline int get_gpio_index(int gpio)
{
	if (cpu_is_omap7xx())
		return gpio & 0x1f;
	if (cpu_is_omap24xx())
		return gpio & 0x1f;
	if (cpu_is_omap34xx() || cpu_is_omap44xx())
		return gpio & 0x1f;
	return gpio & 0x0f;
}