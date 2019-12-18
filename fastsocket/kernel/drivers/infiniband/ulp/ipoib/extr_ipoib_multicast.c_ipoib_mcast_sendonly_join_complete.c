#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_5__ {TYPE_1__ mgid; } ;
struct ipoib_mcast {int /*<<< orphan*/  flags; int /*<<< orphan*/  pkt_queue; TYPE_2__ mcmember; int /*<<< orphan*/  logcount; struct net_device* dev; } ;
struct ib_sa_multicast {int /*<<< orphan*/  rec; struct ipoib_mcast* context; } ;

/* Variables and functions */
 int ENETRESET ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int ipoib_mcast_join_finish (struct ipoib_mcast*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipoib_mcast_sendonly_join_complete(int status,
				   struct ib_sa_multicast *multicast)
{
	struct ipoib_mcast *mcast = multicast->context;
	struct net_device *dev = mcast->dev;

	/* We trap for port events ourselves. */
	if (status == -ENETRESET)
		return 0;

	if (!status)
		status = ipoib_mcast_join_finish(mcast, &multicast->rec);

	if (status) {
		if (mcast->logcount++ < 20)
			ipoib_dbg_mcast(netdev_priv(dev), "multicast join failed for %pI6, status %d\n",
					mcast->mcmember.mgid.raw, status);

		/* Flush out any queued packets */
		netif_tx_lock_bh(dev);
		while (!skb_queue_empty(&mcast->pkt_queue)) {
			++dev->stats.tx_dropped;
			dev_kfree_skb_any(skb_dequeue(&mcast->pkt_queue));
		}
		netif_tx_unlock_bh(dev);

		/* Clear the busy flag so we try again */
		status = test_and_clear_bit(IPOIB_MCAST_FLAG_BUSY,
					    &mcast->flags);
	}
	return status;
}