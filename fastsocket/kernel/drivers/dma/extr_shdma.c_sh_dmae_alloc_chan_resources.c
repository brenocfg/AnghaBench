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
struct sh_dmae_chan {scalar_t__ descs_allocated; int /*<<< orphan*/  desc_lock; int /*<<< orphan*/  common; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_submit; } ;
struct sh_desc {int /*<<< orphan*/  tx_list; TYPE_1__ async_tx; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CTRL_ACK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NR_DESCS_PER_CHANNEL ; 
 int /*<<< orphan*/  dma_async_tx_descriptor_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct sh_desc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_dmae_put_desc (struct sh_dmae_chan*,struct sh_desc*) ; 
 int /*<<< orphan*/  sh_dmae_tx_submit ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sh_dmae_chan* to_sh_chan (struct dma_chan*) ; 

__attribute__((used)) static int sh_dmae_alloc_chan_resources(struct dma_chan *chan)
{
	struct sh_dmae_chan *sh_chan = to_sh_chan(chan);
	struct sh_desc *desc;

	spin_lock_bh(&sh_chan->desc_lock);
	while (sh_chan->descs_allocated < NR_DESCS_PER_CHANNEL) {
		spin_unlock_bh(&sh_chan->desc_lock);
		desc = kzalloc(sizeof(struct sh_desc), GFP_KERNEL);
		if (!desc) {
			spin_lock_bh(&sh_chan->desc_lock);
			break;
		}
		dma_async_tx_descriptor_init(&desc->async_tx,
					&sh_chan->common);
		desc->async_tx.tx_submit = sh_dmae_tx_submit;
		desc->async_tx.flags = DMA_CTRL_ACK;
		INIT_LIST_HEAD(&desc->tx_list);
		sh_dmae_put_desc(sh_chan, desc);

		spin_lock_bh(&sh_chan->desc_lock);
		sh_chan->descs_allocated++;
	}
	spin_unlock_bh(&sh_chan->desc_lock);

	return sh_chan->descs_allocated;
}