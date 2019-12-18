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
 int EINVAL ; 
 int* irq2gpio ; 

int irq_to_gpio(int irq)
{
	int gpio = (irq < 32) ? irq2gpio[irq] : -EINVAL;

	if (gpio == -1)
		return -EINVAL;

	return gpio;
}