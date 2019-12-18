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
 int FAN_ALWAYS_ON ; 
 int FAN_OFF ; 
 int FAN_ON ; 
 int GPIO_FAN ; 
 int nw_gpio_read () ; 
 int system_rev ; 

__attribute__((used)) static inline int netwinder_get_fan(void)
{
	if ((system_rev & 0xf000) == 0x4000)
		return FAN_ALWAYS_ON;

	return (nw_gpio_read() & GPIO_FAN) ? FAN_ON : FAN_OFF;
}