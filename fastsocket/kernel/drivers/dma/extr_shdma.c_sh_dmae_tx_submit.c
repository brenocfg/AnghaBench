#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  prev; } ;
struct TYPE_4__ {int cookie; } ;
struct sh_dmae_chan {int /*<<< orphan*/  desc_lock; TYPE_3__ ld_queue; TYPE_1__ common; } ;
struct TYPE_5__ {int cookie; } ;
struct sh_desc {int /*<<< orphan*/  tx_list; TYPE_2__ async_tx; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int dma_cookie_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sh_dmae_chan* to_sh_chan (int /*<<< orphan*/ ) ; 
 struct sh_desc* tx_to_sh_desc (struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t sh_dmae_tx_submit(struct dma_async_tx_descriptor *tx)
{
	struct sh_desc *desc = tx_to_sh_desc(tx);
	struct sh_dmae_chan *sh_chan = to_sh_chan(tx->chan);
	dma_cookie_t cookie;

	spin_lock_bh(&sh_chan->desc_lock);

	cookie = sh_chan->common.cookie;
	cookie++;
	if (cookie < 0)
		cookie = 1;

	/* If desc only in the case of 1 */
	if (desc->async_tx.cookie != -EBUSY)
		desc->async_tx.cookie = cookie;
	sh_chan->common.cookie = desc->async_tx.cookie;

	list_splice_init(&desc->tx_list, sh_chan->ld_queue.prev);

	spin_unlock_bh(&sh_chan->desc_lock);

	return cookie;
}