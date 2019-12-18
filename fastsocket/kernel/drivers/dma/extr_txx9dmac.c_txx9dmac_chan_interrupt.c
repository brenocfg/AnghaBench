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
struct txx9dmac_chan {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  channel_readl (struct txx9dmac_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_nosync (int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t txx9dmac_chan_interrupt(int irq, void *dev_id)
{
	struct txx9dmac_chan *dc = dev_id;

	dev_vdbg(chan2dev(&dc->chan), "interrupt: status=%#x\n",
			channel_readl(dc, CSR));

	tasklet_schedule(&dc->tasklet);
	/*
	 * Just disable the interrupts. We'll turn them back on in the
	 * softirq handler.
	 */
	disable_irq_nosync(irq);

	return IRQ_HANDLED;
}