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
 scalar_t__ S6_GPIO_AFSEL ; 
 scalar_t__ S6_GPIO_BANK (int) ; 
 scalar_t__ S6_REG_GPIO ; 
 int /*<<< orphan*/  gpiochip ; 
 int gpiochip_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

int s6_gpio_init(u32 afsel)
{
	writeb(afsel, S6_REG_GPIO + S6_GPIO_BANK(0) + S6_GPIO_AFSEL);
	writeb(afsel >> 8, S6_REG_GPIO + S6_GPIO_BANK(1) + S6_GPIO_AFSEL);
	writeb(afsel >> 16, S6_REG_GPIO + S6_GPIO_BANK(2) + S6_GPIO_AFSEL);
	return gpiochip_add(&gpiochip);
}