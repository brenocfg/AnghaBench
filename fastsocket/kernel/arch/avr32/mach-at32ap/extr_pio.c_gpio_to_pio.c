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
struct pio_device {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 unsigned int MAX_NR_PIO_DEVICES ; 
 struct pio_device* pio_dev ; 

__attribute__((used)) static struct pio_device *gpio_to_pio(unsigned int gpio)
{
	struct pio_device *pio;
	unsigned int index;

	index = gpio >> 5;
	if (index >= MAX_NR_PIO_DEVICES)
		return NULL;
	pio = &pio_dev[index];
	if (!pio->regs)
		return NULL;

	return pio;
}