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
struct ipu {int /*<<< orphan*/  lock; } ;
struct idmac_channel {int /*<<< orphan*/  active_buffer; } ;
struct idmac {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  chan_id; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipu_select_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct idmac* to_idmac (int /*<<< orphan*/ ) ; 
 struct idmac_channel* to_idmac_chan (struct dma_chan*) ; 
 struct ipu* to_ipu (struct idmac*) ; 

__attribute__((used)) static void idmac_issue_pending(struct dma_chan *chan)
{
	struct idmac_channel *ichan = to_idmac_chan(chan);
	struct idmac *idmac = to_idmac(chan->device);
	struct ipu *ipu = to_ipu(idmac);
	unsigned long flags;

	/* This is not always needed, but doesn't hurt either */
	spin_lock_irqsave(&ipu->lock, flags);
	ipu_select_buffer(chan->chan_id, ichan->active_buffer);
	spin_unlock_irqrestore(&ipu->lock, flags);

	/*
	 * Might need to perform some parts of initialisation from
	 * ipu_enable_channel(), but not all, we do not want to reset to buffer
	 * 0, don't need to set priority again either, but re-enabling the task
	 * and the channel might be a good idea.
	 */
}