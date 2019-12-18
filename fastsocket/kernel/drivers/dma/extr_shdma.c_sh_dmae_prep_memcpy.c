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
struct sh_dmae_chan {int /*<<< orphan*/  dev; } ;
struct dma_async_tx_descriptor {unsigned long flags; int /*<<< orphan*/  cookie; } ;
struct TYPE_2__ {size_t sar; size_t dar; size_t tcr; } ;
struct sh_desc {struct dma_async_tx_descriptor async_tx; int /*<<< orphan*/  tx_list; int /*<<< orphan*/  node; int /*<<< orphan*/  mark; TYPE_1__ hw; } ;
struct dma_chan {int dummy; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_NCOMP ; 
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ SH_DMA_TCR_MAX ; 
 int /*<<< orphan*/  async_tx_ack (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t min (size_t,size_t) ; 
 struct sh_desc* sh_dmae_get_desc (struct sh_dmae_chan*) ; 
 int /*<<< orphan*/  sh_dmae_put_desc (struct sh_dmae_chan*,struct sh_desc*) ; 
 struct sh_dmae_chan* to_sh_chan (struct dma_chan*) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *sh_dmae_prep_memcpy(
	struct dma_chan *chan, dma_addr_t dma_dest, dma_addr_t dma_src,
	size_t len, unsigned long flags)
{
	struct sh_dmae_chan *sh_chan;
	struct sh_desc *first = NULL, *prev = NULL, *new;
	size_t copy_size;

	if (!chan)
		return NULL;

	if (!len)
		return NULL;

	sh_chan = to_sh_chan(chan);

	do {
		/* Allocate the link descriptor from DMA pool */
		new = sh_dmae_get_desc(sh_chan);
		if (!new) {
			dev_err(sh_chan->dev,
					"No free memory for link descriptor\n");
			goto err_get_desc;
		}

		copy_size = min(len, (size_t)SH_DMA_TCR_MAX);

		new->hw.sar = dma_src;
		new->hw.dar = dma_dest;
		new->hw.tcr = copy_size;
		if (!first)
			first = new;

		new->mark = DESC_NCOMP;
		async_tx_ack(&new->async_tx);

		prev = new;
		len -= copy_size;
		dma_src += copy_size;
		dma_dest += copy_size;
		/* Insert the link descriptor to the LD ring */
		list_add_tail(&new->node, &first->tx_list);
	} while (len);

	new->async_tx.flags = flags; /* client is in control of this ack */
	new->async_tx.cookie = -EBUSY; /* Last desc */

	return &first->async_tx;

err_get_desc:
	sh_dmae_put_desc(sh_chan, first);
	return NULL;

}