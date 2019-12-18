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
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct TYPE_2__ {int /*<<< orphan*/  plx9080_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  plx9080_abort_dma (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void abort_dma(struct comedi_device *dev, unsigned int channel)
{
	unsigned long flags;

	/*  spinlock for plx dma control/status reg */
	spin_lock_irqsave(&dev->spinlock, flags);

	plx9080_abort_dma(priv(dev)->plx9080_iobase, channel);

	spin_unlock_irqrestore(&dev->spinlock, flags);
}