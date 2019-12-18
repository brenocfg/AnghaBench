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
typedef  int u64 ;
typedef  int u32 ;
struct gem_txd {int dummy; } ;
struct gem {int rx_pause_off; int rx_pause_on; scalar_t__ regs; int /*<<< orphan*/  gblock_dvma; } ;

/* Variables and functions */
 scalar_t__ GREG_BIFCFG ; 
 int GREG_BIFCFG_M66EN ; 
 int INIT_BLOCK_TX_RING_SIZE ; 
 scalar_t__ RXDMA_BLANK ; 
 int RXDMA_BLANK_IPKTS ; 
 int RXDMA_BLANK_ITIME ; 
 scalar_t__ RXDMA_CFG ; 
 int RXDMA_CFG_BASE ; 
 int RXDMA_CFG_FTHRESH_128 ; 
 scalar_t__ RXDMA_DBHI ; 
 scalar_t__ RXDMA_DBLOW ; 
 scalar_t__ RXDMA_KICK ; 
 scalar_t__ RXDMA_PTHRESH ; 
 int RXDMA_PTHRESH_OFF ; 
 int RXDMA_PTHRESH_ON ; 
 int RX_OFFSET ; 
 int RX_RING_SIZE ; 
 scalar_t__ TXDMA_CFG ; 
 int TXDMA_CFG_BASE ; 
 int TXDMA_CFG_PMODE ; 
 scalar_t__ TXDMA_DBHI ; 
 scalar_t__ TXDMA_DBLOW ; 
 scalar_t__ TXDMA_KICK ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void gem_init_dma(struct gem *gp)
{
	u64 desc_dma = (u64) gp->gblock_dvma;
	u32 val;

	val = (TXDMA_CFG_BASE | (0x7ff << 10) | TXDMA_CFG_PMODE);
	writel(val, gp->regs + TXDMA_CFG);

	writel(desc_dma >> 32, gp->regs + TXDMA_DBHI);
	writel(desc_dma & 0xffffffff, gp->regs + TXDMA_DBLOW);
	desc_dma += (INIT_BLOCK_TX_RING_SIZE * sizeof(struct gem_txd));

	writel(0, gp->regs + TXDMA_KICK);

	val = (RXDMA_CFG_BASE | (RX_OFFSET << 10) |
	       ((14 / 2) << 13) | RXDMA_CFG_FTHRESH_128);
	writel(val, gp->regs + RXDMA_CFG);

	writel(desc_dma >> 32, gp->regs + RXDMA_DBHI);
	writel(desc_dma & 0xffffffff, gp->regs + RXDMA_DBLOW);

	writel(RX_RING_SIZE - 4, gp->regs + RXDMA_KICK);

	val  = (((gp->rx_pause_off / 64) << 0) & RXDMA_PTHRESH_OFF);
	val |= (((gp->rx_pause_on / 64) << 12) & RXDMA_PTHRESH_ON);
	writel(val, gp->regs + RXDMA_PTHRESH);

	if (readl(gp->regs + GREG_BIFCFG) & GREG_BIFCFG_M66EN)
		writel(((5 & RXDMA_BLANK_IPKTS) |
			((8 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
	else
		writel(((5 & RXDMA_BLANK_IPKTS) |
			((4 << 12) & RXDMA_BLANK_ITIME)),
		       gp->regs + RXDMA_BLANK);
}