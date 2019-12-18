#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_7__ {scalar_t__ tx_pkt_cnt; int /*<<< orphan*/  queue_pkt_len; int /*<<< orphan*/  queue_ip_summed; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ board_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_NSR ; 
 int NSR_TX1END ; 
 int NSR_TX2END ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dm9000_send_packet (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ior (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_tx_done (TYPE_2__*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void dm9000_tx_done(struct net_device *dev, board_info_t *db)
{
	int tx_status = ior(db, DM9000_NSR);	/* Got TX status */

	if (tx_status & (NSR_TX2END | NSR_TX1END)) {
		/* One packet sent complete */
		db->tx_pkt_cnt--;
		dev->stats.tx_packets++;

		if (netif_msg_tx_done(db))
			dev_dbg(db->dev, "tx done, NSR %02x\n", tx_status);

		/* Queue packet check & send */
		if (db->tx_pkt_cnt > 0)
			dm9000_send_packet(dev, db->queue_ip_summed,
					   db->queue_pkt_len);
		netif_wake_queue(dev);
	}
}