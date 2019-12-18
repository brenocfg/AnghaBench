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
struct ni_gpct {int /*<<< orphan*/  counter_index; int /*<<< orphan*/  lock; scalar_t__ mite_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  Gi_Gate_Interrupt_Enable_Bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Interrupt_Enable_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_dma_disarm (scalar_t__) ; 
 int /*<<< orphan*/  ni_tio_arm (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_configure_dma (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ni_tio_cancel(struct ni_gpct *counter)
{
	unsigned long flags;

	ni_tio_arm(counter, 0, 0);
	spin_lock_irqsave(&counter->lock, flags);
	if (counter->mite_chan) {
		mite_dma_disarm(counter->mite_chan);
	}
	spin_unlock_irqrestore(&counter->lock, flags);
	ni_tio_configure_dma(counter, 0, 0);

	ni_tio_set_bits(counter,
			NITIO_Gi_Interrupt_Enable_Reg(counter->counter_index),
			Gi_Gate_Interrupt_Enable_Bit(counter->counter_index),
			0x0);
	return 0;
}