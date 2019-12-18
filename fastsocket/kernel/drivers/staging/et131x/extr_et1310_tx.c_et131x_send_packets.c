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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_4__ {int /*<<< orphan*/  SendWaitQueue; } ;
struct et131x_adapter {TYPE_1__ net_stats; scalar_t__ DriverNoPhyAccess; TYPE_2__ TxRing; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MP_SHOULD_FAIL_SEND (struct et131x_adapter*) ; 
 scalar_t__ MP_TCB_RESOURCES_NOT_AVAILABLE (struct et131x_adapter*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int et131x_send_packet (struct sk_buff*,struct et131x_adapter*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_ok (struct net_device*) ; 

int et131x_send_packets(struct sk_buff *skb, struct net_device *netdev)
{
	int status = 0;
	struct et131x_adapter *etdev = NULL;

	etdev = netdev_priv(netdev);

	/* Send these packets
	 *
	 * NOTE: The Linux Tx entry point is only given one packet at a time
	 * to Tx, so the PacketCount and it's array used makes no sense here
	 */

	/* Queue is not empty or TCB is not available */
	if (!list_empty(&etdev->TxRing.SendWaitQueue) ||
	    MP_TCB_RESOURCES_NOT_AVAILABLE(etdev)) {
		/* NOTE: If there's an error on send, no need to queue the
		 * packet under Linux; if we just send an error up to the
		 * netif layer, it will resend the skb to us.
		 */
		status = -ENOMEM;
	} else {
		/* We need to see if the link is up; if it's not, make the
		 * netif layer think we're good and drop the packet
		 */
		/*
		 * if( MP_SHOULD_FAIL_SEND( etdev ) ||
		 *  etdev->DriverNoPhyAccess )
		 */
		if (MP_SHOULD_FAIL_SEND(etdev) || etdev->DriverNoPhyAccess
		    || !netif_carrier_ok(netdev)) {
			dev_kfree_skb_any(skb);
			skb = NULL;

			etdev->net_stats.tx_dropped++;
		} else {
			status = et131x_send_packet(skb, etdev);

			if (status == -ENOMEM) {

				/* NOTE: If there's an error on send, no need
				 * to queue the packet under Linux; if we just
				 * send an error up to the netif layer, it
				 * will resend the skb to us.
				 */
			} else if (status != 0) {
				/* On any other error, make netif think we're
				 * OK and drop the packet
				 */
				dev_kfree_skb_any(skb);
				skb = NULL;
				etdev->net_stats.tx_dropped++;
			}
		}
	}
	return status;
}