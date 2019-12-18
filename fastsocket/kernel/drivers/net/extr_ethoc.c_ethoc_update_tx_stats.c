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
struct net_device {int /*<<< orphan*/  dev; } ;
struct ethoc_bd {int stat; } ;
struct TYPE_2__ {int collisions; int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_aborted_errors; int /*<<< orphan*/  tx_window_errors; } ;
struct ethoc {TYPE_1__ stats; struct net_device* netdev; } ;

/* Variables and functions */
 int TX_BD_CS ; 
 int TX_BD_LC ; 
 int TX_BD_RL ; 
 int TX_BD_STATS ; 
 int TX_BD_UR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ethoc_update_tx_stats(struct ethoc *dev, struct ethoc_bd *bd)
{
	struct net_device *netdev = dev->netdev;

	if (bd->stat & TX_BD_LC) {
		dev_err(&netdev->dev, "TX: late collision\n");
		dev->stats.tx_window_errors++;
	}

	if (bd->stat & TX_BD_RL) {
		dev_err(&netdev->dev, "TX: retransmit limit\n");
		dev->stats.tx_aborted_errors++;
	}

	if (bd->stat & TX_BD_UR) {
		dev_err(&netdev->dev, "TX: underrun\n");
		dev->stats.tx_fifo_errors++;
	}

	if (bd->stat & TX_BD_CS) {
		dev_err(&netdev->dev, "TX: carrier sense lost\n");
		dev->stats.tx_carrier_errors++;
	}

	if (bd->stat & TX_BD_STATS)
		dev->stats.tx_errors++;

	dev->stats.collisions += (bd->stat >> 4) & 0xf;
	dev->stats.tx_bytes += bd->stat >> 16;
	dev->stats.tx_packets++;
	return 0;
}