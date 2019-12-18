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
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; TYPE_1__* sk; struct net_device* dev; } ;
struct net_device {long features; TYPE_2__* ethtool_ops; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* get_drvinfo ) (struct net_device*,struct ethtool_drvinfo*) ;} ;
struct TYPE_3__ {long sk_route_caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,long,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct ethtool_drvinfo*) ; 

__attribute__((used)) static void skb_warn_bad_offload(const struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	struct ethtool_drvinfo info = {};

	if (dev && dev->ethtool_ops && dev->ethtool_ops->get_drvinfo)
		dev->ethtool_ops->get_drvinfo(dev, &info);

	WARN(1, "%s: caps=(0x%lx, 0x%lx) len=%d data_len=%d "
		"ip_summed=%d",
	     info.driver, dev ? dev->features : 0L,
	     skb->sk ? skb->sk->sk_route_caps : 0L,
	     skb->len, skb->data_len, skb->ip_summed);
}