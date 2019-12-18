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
 int PIN_TO_PORT (unsigned int) ; 
 int U300_GPIO_PORTX_SPACING ; 
 scalar_t__ U300_GPIO_PXPDIR ; 
 int readl (scalar_t__) ; 
 scalar_t__ virtbase ; 

int gpio_get_value(unsigned gpio)
{
	return readl(virtbase + U300_GPIO_PXPDIR +
	  PIN_TO_PORT(gpio) * U300_GPIO_PORTX_SPACING) & (1 << (gpio & 0x07));
}