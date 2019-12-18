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
typedef  int u64 ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;
struct TYPE_3__ {int rx_frags; } ;
struct cp_private {TYPE_2__* pdev; TYPE_1__ cp_stats; } ;
struct cp_dma_stats {int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  tx_abort; int /*<<< orphan*/  rx_ok_mcast; int /*<<< orphan*/  rx_ok_bcast; int /*<<< orphan*/  rx_ok_phys; int /*<<< orphan*/  tx_ok_mcol; int /*<<< orphan*/  tx_ok_1col; int /*<<< orphan*/  frame_align; int /*<<< orphan*/  rx_fifo; int /*<<< orphan*/  rx_err; int /*<<< orphan*/  tx_err; int /*<<< orphan*/  rx_ok; int /*<<< orphan*/  tx_ok; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CP_NUM_STATS ; 
 int DMA_BIT_MASK (int) ; 
 int DumpStats ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ StatsAddr ; 
 int cpr32 (scalar_t__) ; 
 int /*<<< orphan*/  cpw32 (scalar_t__,int) ; 
 struct cp_dma_stats* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,struct cp_dma_stats*,scalar_t__) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cp_get_ethtool_stats (struct net_device *dev,
				  struct ethtool_stats *estats, u64 *tmp_stats)
{
	struct cp_private *cp = netdev_priv(dev);
	struct cp_dma_stats *nic_stats;
	dma_addr_t dma;
	int i;

	nic_stats = dma_alloc_coherent(&cp->pdev->dev, sizeof(*nic_stats),
				       &dma, GFP_KERNEL);
	if (!nic_stats)
		return;

	/* begin NIC statistics dump */
	cpw32(StatsAddr + 4, (u64)dma >> 32);
	cpw32(StatsAddr, ((u64)dma & DMA_BIT_MASK(32)) | DumpStats);
	cpr32(StatsAddr);

	for (i = 0; i < 1000; i++) {
		if ((cpr32(StatsAddr) & DumpStats) == 0)
			break;
		udelay(10);
	}
	cpw32(StatsAddr, 0);
	cpw32(StatsAddr + 4, 0);
	cpr32(StatsAddr);

	i = 0;
	tmp_stats[i++] = le64_to_cpu(nic_stats->tx_ok);
	tmp_stats[i++] = le64_to_cpu(nic_stats->rx_ok);
	tmp_stats[i++] = le64_to_cpu(nic_stats->tx_err);
	tmp_stats[i++] = le32_to_cpu(nic_stats->rx_err);
	tmp_stats[i++] = le16_to_cpu(nic_stats->rx_fifo);
	tmp_stats[i++] = le16_to_cpu(nic_stats->frame_align);
	tmp_stats[i++] = le32_to_cpu(nic_stats->tx_ok_1col);
	tmp_stats[i++] = le32_to_cpu(nic_stats->tx_ok_mcol);
	tmp_stats[i++] = le64_to_cpu(nic_stats->rx_ok_phys);
	tmp_stats[i++] = le64_to_cpu(nic_stats->rx_ok_bcast);
	tmp_stats[i++] = le32_to_cpu(nic_stats->rx_ok_mcast);
	tmp_stats[i++] = le16_to_cpu(nic_stats->tx_abort);
	tmp_stats[i++] = le16_to_cpu(nic_stats->tx_underrun);
	tmp_stats[i++] = cp->cp_stats.rx_frags;
	BUG_ON(i != CP_NUM_STATS);

	dma_free_coherent(&cp->pdev->dev, sizeof(*nic_stats), nic_stats, dma);
}