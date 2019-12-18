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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  real_num_tx_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_tx_hash (struct net_device const*,struct sk_buff const*,int /*<<< orphan*/ ) ; 

u16 skb_tx_hash(const struct net_device *dev, const struct sk_buff *skb)
{
	return __skb_tx_hash(dev, skb, dev->real_num_tx_queues);
}