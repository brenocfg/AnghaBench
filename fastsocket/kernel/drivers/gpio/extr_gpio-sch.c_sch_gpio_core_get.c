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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int CGLV ; 
 scalar_t__ gpio_ba ; 
 int inb (scalar_t__) ; 

__attribute__((used)) static int sch_gpio_core_get(struct gpio_chip *gc, unsigned gpio_num)
{
	int res;
	unsigned short offset, bit;

	offset = CGLV + gpio_num / 8;
	bit = gpio_num % 8;

	res = !!(inb(gpio_ba + offset) & (1 << bit));
	return res;
}