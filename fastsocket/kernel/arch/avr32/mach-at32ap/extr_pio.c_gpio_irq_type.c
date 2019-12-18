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
 unsigned int IRQ_TYPE_EDGE_BOTH ; 
 unsigned int IRQ_TYPE_NONE ; 

__attribute__((used)) static int gpio_irq_type(unsigned irq, unsigned type)
{
	if (type != IRQ_TYPE_EDGE_BOTH && type != IRQ_TYPE_NONE)
		return -EINVAL;

	return 0;
}