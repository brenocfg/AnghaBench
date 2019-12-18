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
struct net_device {int /*<<< orphan*/  ip6_ptr; } ;
struct net {int dummy; } ;
struct inet6_ifaddr {int dead; struct inet6_ifaddr* if_next; int /*<<< orphan*/  lock; struct inet6_ifaddr* ifpub; struct inet6_ifaddr* tmp_next; struct inet6_ifaddr* lst_next; struct inet6_dev* idev; } ;
struct inet6_dev {int dead; int if_flags; int /*<<< orphan*/  nd_parms; int /*<<< orphan*/  tstamp; int /*<<< orphan*/  lock; struct inet6_ifaddr* addr_list; struct inet6_ifaddr* tempaddr_list; int /*<<< orphan*/  regen_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int ENODEV ; 
 int IF_RA_RCVD ; 
 int IF_READY ; 
 int IF_RS_SENT ; 
 int IN6_ADDR_HSIZE ; 
 int INET6_IFADDR_STATE_DEAD ; 
 int /*<<< orphan*/  NETDEV_DOWN ; 
 int /*<<< orphan*/  RTM_DELADDR ; 
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  __ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_del_timer (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_hash_lock ; 
 int /*<<< orphan*/  addrconf_sysctl_unregister (struct inet6_dev*) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  ifa_state_lock ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr** inet6_addr_lst ; 
 int /*<<< orphan*/  inet6addr_chain ; 
 int /*<<< orphan*/  ipv6_mc_destroy_dev (struct inet6_dev*) ; 
 int /*<<< orphan*/  ipv6_mc_down (struct inet6_dev*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  nd_tbl ; 
 int /*<<< orphan*/  neigh_ifdown (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_parms_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt6_ifdown (struct net*,struct net_device*) ; 
 int /*<<< orphan*/  snmp6_unregister_dev (struct inet6_dev*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int addrconf_ifdown(struct net_device *dev, int how)
{
	struct inet6_dev *idev;
	struct inet6_ifaddr *ifa, **bifa;
	struct net *net = dev_net(dev);
	int state;
	int i;

	ASSERT_RTNL();

	rt6_ifdown(net, dev);
	neigh_ifdown(&nd_tbl, dev);

	idev = __in6_dev_get(dev);
	if (idev == NULL)
		return -ENODEV;

	/* Step 1: remove reference to ipv6 device from parent device.
		   Do not dev_put!
	 */
	if (how) {
		idev->dead = 1;

		/* protected by rtnl_lock */
		rcu_assign_pointer(dev->ip6_ptr, NULL);

		/* Step 1.5: remove snmp6 entry */
		snmp6_unregister_dev(idev);

	}

	/* Step 2: clear hash table */
	for (i=0; i<IN6_ADDR_HSIZE; i++) {
		bifa = &inet6_addr_lst[i];

		write_lock_bh(&addrconf_hash_lock);
		while ((ifa = *bifa) != NULL) {
			if (ifa->idev == idev) {
				*bifa = ifa->lst_next;
				ifa->lst_next = NULL;
				addrconf_del_timer(ifa);
				in6_ifa_put(ifa);
				continue;
			}
			bifa = &ifa->lst_next;
		}
		write_unlock_bh(&addrconf_hash_lock);
	}

	write_lock_bh(&idev->lock);

	/* Step 3: clear flags for stateless addrconf */
	if (!how)
		idev->if_flags &= ~(IF_RS_SENT|IF_RA_RCVD|IF_READY);

	/* Step 4: clear address list */
#ifdef CONFIG_IPV6_PRIVACY
	if (how && del_timer(&idev->regen_timer))
		in6_dev_put(idev);

	/* clear tempaddr list */
	while ((ifa = idev->tempaddr_list) != NULL) {
		idev->tempaddr_list = ifa->tmp_next;
		ifa->tmp_next = NULL;
		write_unlock_bh(&idev->lock);
		spin_lock_bh(&ifa->lock);

		if (ifa->ifpub) {
			in6_ifa_put(ifa->ifpub);
			ifa->ifpub = NULL;
		}
		spin_unlock_bh(&ifa->lock);
		in6_ifa_put(ifa);
		write_lock_bh(&idev->lock);
	}
#endif
	while ((ifa = idev->addr_list) != NULL) {
		idev->addr_list = ifa->if_next;
		ifa->if_next = NULL;
		addrconf_del_timer(ifa);
		write_unlock_bh(&idev->lock);
		spin_lock_bh(&ifa_state_lock);
		state = ifa->dead;
		ifa->dead = INET6_IFADDR_STATE_DEAD;
		spin_unlock_bh(&ifa_state_lock);

		if (state == INET6_IFADDR_STATE_DEAD)
			goto put_ifa;


		__ipv6_ifa_notify(RTM_DELADDR, ifa);
		atomic_notifier_call_chain(&inet6addr_chain, NETDEV_DOWN, ifa);

put_ifa:
		in6_ifa_put(ifa);

		write_lock_bh(&idev->lock);
	}
	write_unlock_bh(&idev->lock);

	/* Step 5: Discard multicast list */

	if (how)
		ipv6_mc_destroy_dev(idev);
	else
		ipv6_mc_down(idev);

	idev->tstamp = jiffies;

	/* Shot the device (if unregistered) */

	if (how) {
		addrconf_sysctl_unregister(idev);
		neigh_parms_release(&nd_tbl, idev->nd_parms);
		neigh_ifdown(&nd_tbl, dev);
		in6_dev_put(idev);
	}
	return 0;
}