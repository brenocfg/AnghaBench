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
 int /*<<< orphan*/  ack_local_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_to_ip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_group (unsigned int) ; 
 int /*<<< orphan*/  rb532_disable_irq (unsigned int) ; 

__attribute__((used)) static void rb532_mask_and_ack_irq(unsigned int irq_nr)
{
	rb532_disable_irq(irq_nr);
	ack_local_irq(group_to_ip(irq_to_group(irq_nr)));
}