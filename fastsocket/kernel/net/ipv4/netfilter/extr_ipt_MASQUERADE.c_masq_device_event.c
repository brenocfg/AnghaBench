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
struct notifier_block {int dummy; } ;
struct net_device {scalar_t__ ifindex; } ;
struct net {int dummy; } ;

/* Variables and functions */
 unsigned long NETDEV_DOWN ; 
 int /*<<< orphan*/  NF_CT_ASSERT (int) ; 
 int NOTIFY_DONE ; 
 struct net* dev_net (struct net_device const*) ; 
 int /*<<< orphan*/  device_cmp ; 
 int /*<<< orphan*/  nf_ct_iterate_cleanup (struct net*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int masq_device_event(struct notifier_block *this,
			     unsigned long event,
			     void *ptr)
{
	const struct net_device *dev = ptr;
	struct net *net = dev_net(dev);

	if (event == NETDEV_DOWN) {
		/* Device was downed.  Search entire table for
		   conntracks which were associated with that device,
		   and forget them. */
		NF_CT_ASSERT(dev->ifindex != 0);

		nf_ct_iterate_cleanup(net, device_cmp,
				      (void *)(long)dev->ifindex);
	}

	return NOTIFY_DONE;
}