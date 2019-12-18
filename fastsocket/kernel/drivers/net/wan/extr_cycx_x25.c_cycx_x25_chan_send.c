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
struct sk_buff {unsigned int len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {unsigned int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct cycx_x25_channel {TYPE_2__ ifstats; int /*<<< orphan*/  lcn; int /*<<< orphan*/  link; struct cycx_device* card; } ;
struct TYPE_3__ {unsigned int mtu; } ;
struct cycx_device {TYPE_1__ wandev; } ;

/* Variables and functions */
 scalar_t__ cycx_x25_send (struct cycx_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ) ; 
 struct cycx_x25_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,unsigned int) ; 

__attribute__((used)) static int cycx_x25_chan_send(struct net_device *dev, struct sk_buff *skb)
{
	struct cycx_x25_channel *chan = netdev_priv(dev);
	struct cycx_device *card = chan->card;
	int bitm = 0;		/* final packet */
	unsigned len = skb->len;

	if (skb->len > card->wandev.mtu) {
		len = card->wandev.mtu;
		bitm = 0x10;		/* set M-bit (more data) */
	}

	if (cycx_x25_send(card, chan->link, chan->lcn, bitm, len, skb->data))
		return 1;

	if (bitm) {
		skb_pull(skb, len);
		return 1;
	}

	++chan->ifstats.tx_packets;
	chan->ifstats.tx_bytes += len;

	return 0;
}