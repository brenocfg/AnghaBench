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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ GPIO_PORTC ; 
 int gpio_get_value (scalar_t__) ; 

__attribute__((used)) static int pcm970_sdhc2_get_ro(struct device *dev)
{
	return gpio_get_value(GPIO_PORTC + 28);
}