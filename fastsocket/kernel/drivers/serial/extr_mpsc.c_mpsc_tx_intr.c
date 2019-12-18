#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong ;
struct mpsc_tx_desc {int /*<<< orphan*/  bytecnt; int /*<<< orphan*/  cmdstat; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__ icount; } ;
struct mpsc_port_info {int txr_tail; int txr_head; int /*<<< orphan*/  tx_lock; scalar_t__ cache_mgmt; TYPE_2__ port; scalar_t__ txr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int MPSC_TXRE_SIZE ; 
 int MPSC_TXR_ENTRIES ; 
 int SDMA_DESC_CMDSTAT_O ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cache_sync (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_dcache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mpsc_copy_tx_data (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_sdma_start_tx (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  mpsc_sdma_tx_active (struct mpsc_port_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mpsc_tx_intr(struct mpsc_port_info *pi)
{
	struct mpsc_tx_desc *txre;
	int rc = 0;
	unsigned long iflags;

	spin_lock_irqsave(&pi->tx_lock, iflags);

	if (!mpsc_sdma_tx_active(pi)) {
		txre = (struct mpsc_tx_desc *)(pi->txr
				+ (pi->txr_tail * MPSC_TXRE_SIZE));

		dma_cache_sync(pi->port.dev, (void *)txre, MPSC_TXRE_SIZE,
				DMA_FROM_DEVICE);
#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
		if (pi->cache_mgmt) /* GT642[46]0 Res #COMM-2 */
			invalidate_dcache_range((ulong)txre,
					(ulong)txre + MPSC_TXRE_SIZE);
#endif

		while (!(be32_to_cpu(txre->cmdstat) & SDMA_DESC_CMDSTAT_O)) {
			rc = 1;
			pi->port.icount.tx += be16_to_cpu(txre->bytecnt);
			pi->txr_tail = (pi->txr_tail+1) & (MPSC_TXR_ENTRIES-1);

			/* If no more data to tx, fall out of loop */
			if (pi->txr_head == pi->txr_tail)
				break;

			txre = (struct mpsc_tx_desc *)(pi->txr
					+ (pi->txr_tail * MPSC_TXRE_SIZE));
			dma_cache_sync(pi->port.dev, (void *)txre,
					MPSC_TXRE_SIZE, DMA_FROM_DEVICE);
#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
			if (pi->cache_mgmt) /* GT642[46]0 Res #COMM-2 */
				invalidate_dcache_range((ulong)txre,
						(ulong)txre + MPSC_TXRE_SIZE);
#endif
		}

		mpsc_copy_tx_data(pi);
		mpsc_sdma_start_tx(pi);	/* start next desc if ready */
	}

	spin_unlock_irqrestore(&pi->tx_lock, iflags);
	return rc;
}