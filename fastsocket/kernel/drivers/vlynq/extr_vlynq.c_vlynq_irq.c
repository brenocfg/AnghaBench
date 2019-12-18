#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct vlynq_device {scalar_t__ irq_start; TYPE_1__* local; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  int_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  do_IRQ (scalar_t__) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spurious_interrupt () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t vlynq_irq(int irq, void *dev_id)
{
	struct vlynq_device *dev = dev_id;
	u32 status;
	int virq = 0;

	status = readl(&dev->local->int_status);
	writel(status, &dev->local->int_status);

	if (unlikely(!status))
		spurious_interrupt();

	while (status) {
		if (status & 1)
			do_IRQ(dev->irq_start + virq);
		status >>= 1;
		virq++;
	}

	return IRQ_HANDLED;
}