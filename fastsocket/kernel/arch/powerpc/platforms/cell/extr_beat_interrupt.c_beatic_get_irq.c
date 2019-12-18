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
 unsigned int NO_IRQ ; 
 int /*<<< orphan*/  beatic_ack_irq (unsigned int) ; 
 unsigned int beatic_get_irq_plug () ; 

unsigned int beatic_get_irq(void)
{
	unsigned int ret;

	ret = beatic_get_irq_plug();
	if (ret != NO_IRQ)
		beatic_ack_irq(ret);
	return ret;
}