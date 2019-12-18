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
 unsigned int KS8695_IRQ_EXTERN0 ; 
 unsigned int KS8695_IRQ_EXTERN3 ; 

int irq_to_gpio(unsigned int irq)
{
	if ((irq < KS8695_IRQ_EXTERN0) || (irq > KS8695_IRQ_EXTERN3))
		return -EINVAL;

	return (irq - KS8695_IRQ_EXTERN0);
}