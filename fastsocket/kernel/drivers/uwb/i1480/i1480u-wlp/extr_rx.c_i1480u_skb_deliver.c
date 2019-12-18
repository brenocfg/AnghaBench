#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {TYPE_2__ stats; } ;
struct i1480u {scalar_t__ rx_untd_pkt_size; TYPE_3__* rx_skb; int /*<<< orphan*/  rx_srcaddr; int /*<<< orphan*/  wlp; TYPE_1__* usb_iface; struct net_device* net_dev; } ;
struct device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (TYPE_3__*,struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (TYPE_3__*) ; 
 int wlp_receive_frame (struct device*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
void i1480u_skb_deliver(struct i1480u *i1480u)
{
	int should_parse;
	struct net_device *net_dev = i1480u->net_dev;
	struct device *dev = &i1480u->usb_iface->dev;

	should_parse = wlp_receive_frame(dev, &i1480u->wlp, i1480u->rx_skb,
					 &i1480u->rx_srcaddr);
	if (!should_parse)
		goto out;
	i1480u->rx_skb->protocol = eth_type_trans(i1480u->rx_skb, net_dev);
	net_dev->stats.rx_packets++;
	net_dev->stats.rx_bytes += i1480u->rx_untd_pkt_size;

	netif_rx(i1480u->rx_skb);		/* deliver */
out:
	i1480u->rx_skb = NULL;
	i1480u->rx_untd_pkt_size = 0;
}