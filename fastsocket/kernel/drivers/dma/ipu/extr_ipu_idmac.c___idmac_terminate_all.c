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
struct idmac_tx_desc {int /*<<< orphan*/  txd; int /*<<< orphan*/  list; } ;
struct idmac_channel {scalar_t__ status; int n_tx_desc; int /*<<< orphan*/  lock; int /*<<< orphan*/ ** sg; int /*<<< orphan*/  free_list; struct idmac_tx_desc* desc; int /*<<< orphan*/  queue; } ;
struct idmac {int dummy; } ;
struct dma_chan {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 scalar_t__ IPU_CHANNEL_ENABLED ; 
 scalar_t__ IPU_CHANNEL_INITIALIZED ; 
 int /*<<< orphan*/  async_tx_clear_ack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipu_disable_channel (struct idmac*,struct idmac_channel*,int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 struct idmac* to_idmac (int /*<<< orphan*/ ) ; 
 struct idmac_channel* to_idmac_chan (struct dma_chan*) ; 
 TYPE_1__* to_ipu (struct idmac*) ; 

__attribute__((used)) static void __idmac_terminate_all(struct dma_chan *chan)
{
	struct idmac_channel *ichan = to_idmac_chan(chan);
	struct idmac *idmac = to_idmac(chan->device);
	unsigned long flags;
	int i;

	ipu_disable_channel(idmac, ichan,
			    ichan->status >= IPU_CHANNEL_ENABLED);

	tasklet_disable(&to_ipu(idmac)->tasklet);

	/* ichan->queue is modified in ISR, have to spinlock */
	spin_lock_irqsave(&ichan->lock, flags);
	list_splice_init(&ichan->queue, &ichan->free_list);

	if (ichan->desc)
		for (i = 0; i < ichan->n_tx_desc; i++) {
			struct idmac_tx_desc *desc = ichan->desc + i;
			if (list_empty(&desc->list))
				/* Descriptor was prepared, but not submitted */
				list_add(&desc->list, &ichan->free_list);

			async_tx_clear_ack(&desc->txd);
		}

	ichan->sg[0] = NULL;
	ichan->sg[1] = NULL;
	spin_unlock_irqrestore(&ichan->lock, flags);

	tasklet_enable(&to_ipu(idmac)->tasklet);

	ichan->status = IPU_CHANNEL_INITIALIZED;
}