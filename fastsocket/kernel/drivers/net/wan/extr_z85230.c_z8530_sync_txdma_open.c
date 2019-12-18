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
struct z8530_channel {int sync; int mtu; int txdma_on; int tx_dma_used; int dma_ready; int dma_tx; int* regs; int /*<<< orphan*/  lock; int /*<<< orphan*/ * irqs; scalar_t__ rxdma_on; int /*<<< orphan*/  txdma; scalar_t__ dma_num; int /*<<< orphan*/ ** tx_dma_buf; int /*<<< orphan*/ * skb2; int /*<<< orphan*/ * skb; scalar_t__ count; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MODE_WRITE ; 
 int DTRREQ ; 
 int EMSGSIZE ; 
 int ENOBUFS ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int PAGE_SIZE ; 
 size_t R1 ; 
 size_t R14 ; 
 size_t R3 ; 
 int RxENABLE ; 
 int TxINT_ENAB ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,size_t,int) ; 
 int /*<<< orphan*/  z8530_rtsdtr (struct z8530_channel*,int) ; 
 int /*<<< orphan*/  z8530_rx_done (struct z8530_channel*) ; 
 int /*<<< orphan*/  z8530_txdma_sync ; 

int z8530_sync_txdma_open(struct net_device *dev, struct z8530_channel *c)
{
	unsigned long cflags, dflags;

	printk("Opening sync interface for TX-DMA\n");
	c->sync = 1;
	c->mtu = dev->mtu+64;
	c->count = 0;
	c->skb = NULL;
	c->skb2 = NULL;
	
	/*
	 *	Allocate the DMA flip buffers. Limit by page size.
	 *	Everyone runs 1500 mtu or less on wan links so this
	 *	should be fine.
	 */
	 
	if(c->mtu  > PAGE_SIZE/2)
		return -EMSGSIZE;
	 
	c->tx_dma_buf[0]=(void *)get_zeroed_page(GFP_KERNEL|GFP_DMA);
	if(c->tx_dma_buf[0]==NULL)
		return -ENOBUFS;

	c->tx_dma_buf[1] = c->tx_dma_buf[0] + PAGE_SIZE/2;


	spin_lock_irqsave(c->lock, cflags);

	/*
	 *	Load the PIO receive ring
	 */

	z8530_rx_done(c);
	z8530_rx_done(c);

 	/*
	 *	Load the DMA interfaces up
	 */

	c->rxdma_on = 0;
	c->txdma_on = 0;
	
	c->tx_dma_used=0;
	c->dma_num=0;
	c->dma_ready=1;
	c->dma_tx = 1;

 	/*
	 *	Enable DMA control mode
	 */

 	/*
	 *	TX DMA via DIR/REQ
 	 */
	c->regs[R14]|= DTRREQ;
	write_zsreg(c, R14, c->regs[R14]);     
	
	c->regs[R1]&= ~TxINT_ENAB;
	write_zsreg(c, R1, c->regs[R1]);
	
	/*
	 *	Set up the DMA configuration
	 */	
	 
	dflags = claim_dma_lock();

	disable_dma(c->txdma);
	clear_dma_ff(c->txdma);
	set_dma_mode(c->txdma, DMA_MODE_WRITE);
	disable_dma(c->txdma);

	release_dma_lock(dflags);
	
	/*
	 *	Select the DMA interrupt handlers
	 */

	c->rxdma_on = 0;
	c->txdma_on = 1;
	c->tx_dma_used = 1;
	 
	c->irqs = &z8530_txdma_sync;
	z8530_rtsdtr(c,1);
	write_zsreg(c, R3, c->regs[R3]|RxENABLE);
	spin_unlock_irqrestore(c->lock, cflags);
	
	return 0;
}