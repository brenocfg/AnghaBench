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
typedef  scalar_t__ ulong ;
typedef  scalar_t__ u32 ;
struct mpsc_tx_desc {int /*<<< orphan*/  cmdstat; int /*<<< orphan*/  bytecnt; int /*<<< orphan*/  shadow; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mpsc_port_info {int txr_head; scalar_t__ cache_mgmt; TYPE_1__ port; scalar_t__ txr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int MPSC_TXRE_SIZE ; 
 int SDMA_DESC_CMDSTAT_EI ; 
 int SDMA_DESC_CMDSTAT_F ; 
 int SDMA_DESC_CMDSTAT_L ; 
 int SDMA_DESC_CMDSTAT_O ; 
 int /*<<< orphan*/  cpu_to_be16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dma_cache_sync (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_dcache_range (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mpsc_setup_tx_desc(struct mpsc_port_info *pi, u32 count, u32 intr)
{
	struct mpsc_tx_desc *txre;

	txre = (struct mpsc_tx_desc *)(pi->txr
			+ (pi->txr_head * MPSC_TXRE_SIZE));

	txre->bytecnt = cpu_to_be16(count);
	txre->shadow = txre->bytecnt;
	wmb();			/* ensure cmdstat is last field updated */
	txre->cmdstat = cpu_to_be32(SDMA_DESC_CMDSTAT_O | SDMA_DESC_CMDSTAT_F
			| SDMA_DESC_CMDSTAT_L
			| ((intr) ? SDMA_DESC_CMDSTAT_EI : 0));
	wmb();
	dma_cache_sync(pi->port.dev, (void *)txre, MPSC_TXRE_SIZE,
			DMA_BIDIRECTIONAL);
#if defined(CONFIG_PPC32) && !defined(CONFIG_NOT_COHERENT_CACHE)
	if (pi->cache_mgmt) /* GT642[46]0 Res #COMM-2 */
		flush_dcache_range((ulong)txre,
				(ulong)txre + MPSC_TXRE_SIZE);
#endif
}