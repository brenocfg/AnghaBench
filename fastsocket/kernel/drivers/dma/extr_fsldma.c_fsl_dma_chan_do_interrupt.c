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
struct fsl_dma_chan {int /*<<< orphan*/  tasklet; int /*<<< orphan*/  dev; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FSL_DMA_SR_CB ; 
 int FSL_DMA_SR_CH ; 
 int FSL_DMA_SR_EOCDI ; 
 int FSL_DMA_SR_EOLNI ; 
 int FSL_DMA_SR_EOSI ; 
 int FSL_DMA_SR_PE ; 
 int FSL_DMA_SR_TE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fsl_chan_xfer_ld_queue (struct fsl_dma_chan*) ; 
 int /*<<< orphan*/  fsl_dma_update_completed_cookie (struct fsl_dma_chan*) ; 
 scalar_t__ get_bcr (struct fsl_dma_chan*) ; 
 scalar_t__ get_cdar (struct fsl_dma_chan*) ; 
 scalar_t__ get_ndar (struct fsl_dma_chan*) ; 
 int get_sr (struct fsl_dma_chan*) ; 
 int /*<<< orphan*/  set_sr (struct fsl_dma_chan*,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t fsl_dma_chan_do_interrupt(int irq, void *data)
{
	struct fsl_dma_chan *fsl_chan = (struct fsl_dma_chan *)data;
	u32 stat;
	int update_cookie = 0;
	int xfer_ld_q = 0;

	stat = get_sr(fsl_chan);
	dev_dbg(fsl_chan->dev, "event: channel %d, stat = 0x%x\n",
						fsl_chan->id, stat);
	set_sr(fsl_chan, stat);		/* Clear the event register */

	stat &= ~(FSL_DMA_SR_CB | FSL_DMA_SR_CH);
	if (!stat)
		return IRQ_NONE;

	if (stat & FSL_DMA_SR_TE)
		dev_err(fsl_chan->dev, "Transfer Error!\n");

	/* Programming Error
	 * The DMA_INTERRUPT async_tx is a NULL transfer, which will
	 * triger a PE interrupt.
	 */
	if (stat & FSL_DMA_SR_PE) {
		dev_dbg(fsl_chan->dev, "event: Programming Error INT\n");
		if (get_bcr(fsl_chan) == 0) {
			/* BCR register is 0, this is a DMA_INTERRUPT async_tx.
			 * Now, update the completed cookie, and continue the
			 * next uncompleted transfer.
			 */
			update_cookie = 1;
			xfer_ld_q = 1;
		}
		stat &= ~FSL_DMA_SR_PE;
	}

	/* If the link descriptor segment transfer finishes,
	 * we will recycle the used descriptor.
	 */
	if (stat & FSL_DMA_SR_EOSI) {
		dev_dbg(fsl_chan->dev, "event: End-of-segments INT\n");
		dev_dbg(fsl_chan->dev, "event: clndar 0x%llx, nlndar 0x%llx\n",
			(unsigned long long)get_cdar(fsl_chan),
			(unsigned long long)get_ndar(fsl_chan));
		stat &= ~FSL_DMA_SR_EOSI;
		update_cookie = 1;
	}

	/* For MPC8349, EOCDI event need to update cookie
	 * and start the next transfer if it exist.
	 */
	if (stat & FSL_DMA_SR_EOCDI) {
		dev_dbg(fsl_chan->dev, "event: End-of-Chain link INT\n");
		stat &= ~FSL_DMA_SR_EOCDI;
		update_cookie = 1;
		xfer_ld_q = 1;
	}

	/* If it current transfer is the end-of-transfer,
	 * we should clear the Channel Start bit for
	 * prepare next transfer.
	 */
	if (stat & FSL_DMA_SR_EOLNI) {
		dev_dbg(fsl_chan->dev, "event: End-of-link INT\n");
		stat &= ~FSL_DMA_SR_EOLNI;
		xfer_ld_q = 1;
	}

	if (update_cookie)
		fsl_dma_update_completed_cookie(fsl_chan);
	if (xfer_ld_q)
		fsl_chan_xfer_ld_queue(fsl_chan);
	if (stat)
		dev_dbg(fsl_chan->dev, "event: unhandled sr 0x%02x\n",
					stat);

	dev_dbg(fsl_chan->dev, "event: Exit\n");
	tasklet_schedule(&fsl_chan->tasklet);
	return IRQ_HANDLED;
}