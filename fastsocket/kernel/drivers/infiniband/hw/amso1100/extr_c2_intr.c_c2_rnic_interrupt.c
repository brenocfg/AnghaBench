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
struct c2_dev {scalar_t__ hints_read; scalar_t__ regs; int /*<<< orphan*/ * hint_count; } ;

/* Variables and functions */
 scalar_t__ PCI_BAR0_HOST_HINT ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_mq (struct c2_dev*,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 

void c2_rnic_interrupt(struct c2_dev *c2dev)
{
	unsigned int mq_index;

	while (c2dev->hints_read != be16_to_cpu(*c2dev->hint_count)) {
		mq_index = readl(c2dev->regs + PCI_BAR0_HOST_HINT);
		if (mq_index & 0x80000000) {
			break;
		}

		c2dev->hints_read++;
		handle_mq(c2dev, mq_index);
	}

}