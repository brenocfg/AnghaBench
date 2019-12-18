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
struct txx9dmac_chan {int /*<<< orphan*/  completed; int /*<<< orphan*/  lock; } ;
struct dma_chan {int /*<<< orphan*/  cookie; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int DMA_SUCCESS ; 
 int dma_async_is_complete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct txx9dmac_chan* to_txx9dmac_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  txx9dmac_scan_descriptors (struct txx9dmac_chan*) ; 

__attribute__((used)) static enum dma_status
txx9dmac_is_tx_complete(struct dma_chan *chan,
			dma_cookie_t cookie,
		dma_cookie_t *done, dma_cookie_t *used)
{
	struct txx9dmac_chan *dc = to_txx9dmac_chan(chan);
	dma_cookie_t last_used;
	dma_cookie_t last_complete;
	int ret;

	last_complete = dc->completed;
	last_used = chan->cookie;

	ret = dma_async_is_complete(cookie, last_complete, last_used);
	if (ret != DMA_SUCCESS) {
		spin_lock_bh(&dc->lock);
		txx9dmac_scan_descriptors(dc);
		spin_unlock_bh(&dc->lock);

		last_complete = dc->completed;
		last_used = chan->cookie;

		ret = dma_async_is_complete(cookie, last_complete, last_used);
	}

	if (done)
		*done = last_complete;
	if (used)
		*used = last_used;

	return ret;
}