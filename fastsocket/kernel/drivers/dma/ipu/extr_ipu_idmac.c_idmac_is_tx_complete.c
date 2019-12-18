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
struct idmac_channel {scalar_t__ completed; } ;
struct dma_chan {scalar_t__ cookie; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;
typedef  scalar_t__ dma_cookie_t ;

/* Variables and functions */
 int DMA_ERROR ; 
 int DMA_SUCCESS ; 
 struct idmac_channel* to_idmac_chan (struct dma_chan*) ; 

__attribute__((used)) static enum dma_status idmac_is_tx_complete(struct dma_chan *chan,
		dma_cookie_t cookie, dma_cookie_t *done, dma_cookie_t *used)
{
	struct idmac_channel *ichan = to_idmac_chan(chan);

	if (done)
		*done = ichan->completed;
	if (used)
		*used = chan->cookie;
	if (cookie != chan->cookie)
		return DMA_ERROR;
	return DMA_SUCCESS;
}