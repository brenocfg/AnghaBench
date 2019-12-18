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
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  trans_start; } ;

/* Variables and functions */
 int ENOMEM ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int et131x_send_packets (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

int et131x_tx(struct sk_buff *skb, struct net_device *netdev)
{
	int status = 0;

	/* Save the timestamp for the TX timeout watchdog */
	netdev->trans_start = jiffies;

	/* Call the device-specific data Tx routine */
	status = et131x_send_packets(skb, netdev);

	/* Check status and manage the netif queue if necessary */
	if (status != 0) {
		if (status == -ENOMEM) {
			/* Put the queue to sleep until resources are
			 * available
			 */
			netif_stop_queue(netdev);
			status = NETDEV_TX_BUSY;
		} else {
			status = NETDEV_TX_OK;
		}
	}
	return status;
}