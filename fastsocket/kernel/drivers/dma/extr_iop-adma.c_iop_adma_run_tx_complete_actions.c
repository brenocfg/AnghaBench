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
struct dma_async_tx_descriptor {scalar_t__ cookie; int /*<<< orphan*/  callback_param; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;
struct iop_adma_desc_slot {scalar_t__ unmap_len; scalar_t__ group_head; struct dma_async_tx_descriptor async_tx; } ;
struct iop_adma_chan {int dummy; } ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_run_dependencies (struct dma_async_tx_descriptor*) ; 
 scalar_t__ iop_desc_is_pq (struct iop_adma_desc_slot*) ; 
 int /*<<< orphan*/  iop_desc_unmap (struct iop_adma_chan*,struct iop_adma_desc_slot*) ; 
 int /*<<< orphan*/  iop_desc_unmap_pq (struct iop_adma_chan*,struct iop_adma_desc_slot*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static dma_cookie_t
iop_adma_run_tx_complete_actions(struct iop_adma_desc_slot *desc,
	struct iop_adma_chan *iop_chan, dma_cookie_t cookie)
{
	struct dma_async_tx_descriptor *tx = &desc->async_tx;

	BUG_ON(tx->cookie < 0);
	if (tx->cookie > 0) {
		cookie = tx->cookie;
		tx->cookie = 0;

		/* call the callback (must not sleep or submit new
		 * operations to this channel)
		 */
		if (tx->callback)
			tx->callback(tx->callback_param);

		/* unmap dma addresses
		 * (unmap_single vs unmap_page?)
		 */
		if (desc->group_head && desc->unmap_len) {
			if (iop_desc_is_pq(desc))
				iop_desc_unmap_pq(iop_chan, desc);
			else
				iop_desc_unmap(iop_chan, desc);
		}
	}

	/* run dependent operations */
	dma_run_dependencies(tx);

	return cookie;
}