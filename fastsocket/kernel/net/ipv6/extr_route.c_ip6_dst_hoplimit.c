#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_5__ {int hop_limit; } ;
struct inet6_dev {TYPE_1__ cnf; } ;
struct dst_entry {struct net_device* dev; } ;
struct TYPE_7__ {TYPE_2__* devconf_all; } ;
struct TYPE_8__ {TYPE_3__ ipv6; } ;
struct TYPE_6__ {int hop_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTAX_HOPLIMIT ; 
 TYPE_4__* dev_net (struct net_device*) ; 
 int dst_metric (struct dst_entry*,int /*<<< orphan*/ ) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 

int ip6_dst_hoplimit(struct dst_entry *dst)
{
	int hoplimit = dst_metric(dst, RTAX_HOPLIMIT);
	if (hoplimit < 0) {
		struct net_device *dev = dst->dev;
		struct inet6_dev *idev = in6_dev_get(dev);
		if (idev) {
			hoplimit = idev->cnf.hop_limit;
			in6_dev_put(idev);
		} else
			hoplimit = dev_net(dev)->ipv6.devconf_all->hop_limit;
	}
	return hoplimit;
}