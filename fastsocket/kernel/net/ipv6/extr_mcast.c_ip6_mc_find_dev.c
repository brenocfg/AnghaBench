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
struct TYPE_2__ {int /*<<< orphan*/  dst; } ;
struct rt6_info {TYPE_1__ u; struct net_device* rt6i_dev; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  lock; scalar_t__ dead; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_lookup (struct net*,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inet6_dev *ip6_mc_find_dev(struct net *net,
					 struct in6_addr *group,
					 int ifindex)
{
	struct net_device *dev = NULL;
	struct inet6_dev *idev = NULL;

	if (ifindex == 0) {
		struct rt6_info *rt;

		rt = rt6_lookup(net, group, NULL, 0, 0);
		if (rt) {
			dev = rt->rt6i_dev;
			dev_hold(dev);
			dst_release(&rt->u.dst);
		}
	} else
		dev = dev_get_by_index(net, ifindex);

	if (!dev)
		goto nodev;
	idev = in6_dev_get(dev);
	if (!idev)
		goto release;
	read_lock_bh(&idev->lock);
	if (idev->dead)
		goto unlock_release;

	return idev;

unlock_release:
	read_unlock_bh(&idev->lock);
	in6_dev_put(idev);
release:
	dev_put(dev);
nodev:
	return NULL;
}