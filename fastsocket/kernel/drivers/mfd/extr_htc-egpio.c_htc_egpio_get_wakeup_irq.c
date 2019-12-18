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
typedef  int /*<<< orphan*/  u16 ;
struct egpio_info {int irq_start; int /*<<< orphan*/  irqs_enabled; int /*<<< orphan*/  ack_register; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_irqs (struct egpio_info*) ; 
 struct egpio_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  egpio_readw (struct egpio_info*,int /*<<< orphan*/ ) ; 
 int ffs (int /*<<< orphan*/ ) ; 

int htc_egpio_get_wakeup_irq(struct device *dev)
{
	struct egpio_info *ei = dev_get_drvdata(dev);

	/* Read current pins. */
	u16 readval = egpio_readw(ei, ei->ack_register);
	/* Ack/unmask interrupts. */
	ack_irqs(ei);
	/* Return first set pin. */
	readval &= ei->irqs_enabled;
	return ei->irq_start + ffs(readval) - 1;
}