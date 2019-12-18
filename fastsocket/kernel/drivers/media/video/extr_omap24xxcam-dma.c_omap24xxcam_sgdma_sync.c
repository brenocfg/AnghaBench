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
typedef  int /*<<< orphan*/  u32 ;
struct sgdma_state {scalar_t__ next_sglist; void* arg; int /*<<< orphan*/  (* callback ) (struct omap24xxcam_sgdma*,int /*<<< orphan*/ ,void*) ;} ;
struct omap24xxcam_sgdma {int free_sgdma; int next_sgdma; int /*<<< orphan*/  lock; struct sgdma_state* sg_state; int /*<<< orphan*/  dma; } ;
typedef  int /*<<< orphan*/  (* sgdma_callback_t ) (struct omap24xxcam_sgdma*,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  CAMDMA_CSR_TRANS_ERR ; 
 int NUM_SG_DMA ; 
 int /*<<< orphan*/  omap24xxcam_dma_stop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct omap24xxcam_sgdma*,int /*<<< orphan*/ ,void*) ; 

void omap24xxcam_sgdma_sync(struct omap24xxcam_sgdma *sgdma)
{
	unsigned long flags;
	int sgslot;
	struct sgdma_state *sg_state;
	u32 csr = CAMDMA_CSR_TRANS_ERR;

	/* stop any DMA transfers in progress */
	omap24xxcam_dma_stop(&sgdma->dma, csr);

	spin_lock_irqsave(&sgdma->lock, flags);

	if (sgdma->free_sgdma < NUM_SG_DMA) {
		sgslot = (sgdma->next_sgdma + sgdma->free_sgdma) % NUM_SG_DMA;
		sg_state = sgdma->sg_state + sgslot;
		if (sg_state->next_sglist != 0) {
			/* This DMA transfer was in progress, so abort it. */
			sgdma_callback_t callback = sg_state->callback;
			void *arg = sg_state->arg;
			sgdma->free_sgdma++;
			if (callback) {
				/* leave interrupts masked */
				spin_unlock(&sgdma->lock);
				(*callback) (sgdma, csr, arg);
				spin_lock(&sgdma->lock);
			}
		}
	}

	spin_unlock_irqrestore(&sgdma->lock, flags);
}