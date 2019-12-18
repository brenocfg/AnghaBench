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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 TYPE_1__* dev_to_chan (struct net_device*) ; 
 int /*<<< orphan*/  z8530_queue_xmit (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t sealevel_queue_xmit(struct sk_buff *skb,
					     struct net_device *d)
{
	return z8530_queue_xmit(dev_to_chan(d)->chan, skb);
}