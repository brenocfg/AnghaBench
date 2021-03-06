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
typedef  int u32 ;
struct dma_channel {size_t chan; int /*<<< orphan*/  wait_queue; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ CHCR ; 
 int CHCR_DE ; 
 int CHCR_IE ; 
 int CHCR_TE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int ctrl_inl (scalar_t__) ; 
 int /*<<< orphan*/  ctrl_outl (int,scalar_t__) ; 
 scalar_t__* dma_base_addr ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t dma_tei(int irq, void *dev_id)
{
	struct dma_channel *chan = dev_id;
	u32 chcr;

	chcr = ctrl_inl(dma_base_addr[chan->chan] + CHCR);

	if (!(chcr & CHCR_TE))
		return IRQ_NONE;

	chcr &= ~(CHCR_IE | CHCR_DE);
	ctrl_outl(chcr, (dma_base_addr[chan->chan] + CHCR));

	wake_up(&chan->wait_queue);

	return IRQ_HANDLED;
}