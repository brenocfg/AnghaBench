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
struct sk_buff {scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int HvLpIndexMap ;

/* Variables and functions */
 int HVMAXARCHITECTEDLPS ; 
 scalar_t__ veth_transmit_to_one (struct sk_buff*,int,struct net_device*) ; 

__attribute__((used)) static void veth_transmit_to_many(struct sk_buff *skb,
					  HvLpIndexMap lpmask,
					  struct net_device *dev)
{
	int i, success, error;

	success = error = 0;

	for (i = 0; i < HVMAXARCHITECTEDLPS; i++) {
		if ((lpmask & (1 << i)) == 0)
			continue;

		if (veth_transmit_to_one(skb, i, dev))
			error = 1;
		else
			success = 1;
	}

	if (error)
		dev->stats.tx_errors++;

	if (success) {
		dev->stats.tx_packets++;
		dev->stats.tx_bytes += skb->len;
	}
}