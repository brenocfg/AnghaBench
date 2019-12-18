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
struct rionet_private {int rx_slot; TYPE_1__** rx_skb; int /*<<< orphan*/  mport; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RIONET_MAILBOX ; 
 int RIONET_RX_RING_SIZE ; 
 int /*<<< orphan*/  RIO_MAX_MSG_SIZE ; 
 TYPE_1__* dev_alloc_skb (int /*<<< orphan*/ ) ; 
 struct rionet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rio_add_inb_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rionet_rx_fill(struct net_device *ndev, int end)
{
	int i;
	struct rionet_private *rnet = netdev_priv(ndev);

	i = rnet->rx_slot;
	do {
		rnet->rx_skb[i] = dev_alloc_skb(RIO_MAX_MSG_SIZE);

		if (!rnet->rx_skb[i])
			break;

		rio_add_inb_buffer(rnet->mport, RIONET_MAILBOX,
				   rnet->rx_skb[i]->data);
	} while ((i = (i + 1) % RIONET_RX_RING_SIZE) != end);

	rnet->rx_slot = i;
}