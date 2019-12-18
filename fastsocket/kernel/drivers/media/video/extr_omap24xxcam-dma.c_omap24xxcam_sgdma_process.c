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
struct sgdma_state {scalar_t__ next_sglist; scalar_t__ sglen; int const csr; unsigned int len; unsigned int bytes_read; int /*<<< orphan*/  queued_sglist; struct scatterlist* sglist; } ;
struct scatterlist {int dummy; } ;
struct omap24xxcam_sgdma {int free_sgdma; int next_sgdma; int /*<<< orphan*/  lock; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  dma; struct sgdma_state* sg_state; } ;

/* Variables and functions */
 int CAMDMA_CSR_DROP ; 
 int CAMDMA_CSR_MISALIGNED_ERR ; 
 int CAMDMA_CSR_SECURE_ERR ; 
 int CAMDMA_CSR_SUPERVISOR_ERR ; 
 int CAMDMA_CSR_TRANS_ERR ; 
 unsigned long HZ ; 
 int NUM_SG_DMA ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ omap24xxcam_dma_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  omap24xxcam_sgdma_callback ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist const*) ; 
 unsigned int sg_dma_len (struct scatterlist const*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void omap24xxcam_sgdma_process(struct omap24xxcam_sgdma *sgdma)
{
	unsigned long flags;
	int queued_sgdma, sgslot;
	struct sgdma_state *sg_state;
	const u32 csr_error = CAMDMA_CSR_MISALIGNED_ERR
		| CAMDMA_CSR_SUPERVISOR_ERR | CAMDMA_CSR_SECURE_ERR
		| CAMDMA_CSR_TRANS_ERR | CAMDMA_CSR_DROP;

	spin_lock_irqsave(&sgdma->lock, flags);

	queued_sgdma = NUM_SG_DMA - sgdma->free_sgdma;
	sgslot = (sgdma->next_sgdma + sgdma->free_sgdma) % NUM_SG_DMA;
	while (queued_sgdma > 0) {
		sg_state = sgdma->sg_state + sgslot;
		while ((sg_state->next_sglist < sg_state->sglen) &&
		       !(sg_state->csr & csr_error)) {
			const struct scatterlist *sglist;
			unsigned int len;

			sglist = sg_state->sglist + sg_state->next_sglist;
			/* try to start the next DMA transfer */
			if (sg_state->next_sglist + 1 == sg_state->sglen) {
				/*
				 *  On the last sg, we handle the case where
				 *  cam->img.pix.sizeimage % PAGE_ALIGN != 0
				 */
				len = sg_state->len - sg_state->bytes_read;
			} else {
				len = sg_dma_len(sglist);
			}

			if (omap24xxcam_dma_start(&sgdma->dma,
						  sg_dma_address(sglist),
						  len,
						  omap24xxcam_sgdma_callback,
						  (void *)sgslot)) {
				/* DMA start failed */
				spin_unlock_irqrestore(&sgdma->lock, flags);
				return;
			} else {
				unsigned long expires;
				/* DMA start was successful */
				sg_state->next_sglist++;
				sg_state->bytes_read += len;
				sg_state->queued_sglist++;

				/* We start the reset timer */
				expires = jiffies + HZ;
				mod_timer(&sgdma->reset_timer, expires);
			}
		}
		queued_sgdma--;
		sgslot = (sgslot + 1) % NUM_SG_DMA;
	}

	spin_unlock_irqrestore(&sgdma->lock, flags);
}