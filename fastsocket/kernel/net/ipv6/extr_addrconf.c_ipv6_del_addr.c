#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dst; } ;
struct rt6_info {int rt6i_flags; unsigned long rt6i_expires; TYPE_4__ u; } ;
struct TYPE_8__ {struct rt6_info* ip6_null_entry; } ;
struct net {TYPE_3__ ipv6; } ;
struct inet6_ifaddr {int dead; int flags; unsigned long tstamp; struct inet6_dev* idev; int /*<<< orphan*/  prefix_len; int /*<<< orphan*/  addr; struct inet6_ifaddr* if_next; int /*<<< orphan*/  lock; int /*<<< orphan*/  valid_lft; struct inet6_ifaddr* tmp_next; struct inet6_ifaddr* ifpub; struct inet6_ifaddr* lst_next; } ;
struct inet6_dev {TYPE_5__* dev; int /*<<< orphan*/  lock; struct inet6_ifaddr* addr_list; struct inet6_ifaddr* tempaddr_list; } ;
struct in6_addr {int dummy; } ;
struct TYPE_6__ {struct in6_addr daddr; } ;
struct TYPE_7__ {TYPE_1__ ip6_u; } ;
struct flowi {TYPE_2__ nl_u; int /*<<< orphan*/  oif; } ;
struct TYPE_10__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 unsigned long HZ ; 
 int IFA_F_PERMANENT ; 
 int IFA_F_TEMPORARY ; 
 int INET6_IFADDR_STATE_DEAD ; 
 int /*<<< orphan*/  NETDEV_DOWN ; 
 int /*<<< orphan*/  RT6_LOOKUP_F_IFACE ; 
 int RTF_EXPIRES ; 
 int /*<<< orphan*/  RTM_DELADDR ; 
 int /*<<< orphan*/  __in6_ifa_put (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_del_timer (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  addrconf_hash_lock ; 
 scalar_t__ addrconf_is_prefix_route (struct rt6_info*) ; 
 unsigned long addrconf_timeout_fixup (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  atomic_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 struct net* dev_net (TYPE_5__*) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifa_state_lock ; 
 int /*<<< orphan*/  in6_ifa_put (struct inet6_ifaddr*) ; 
 struct inet6_ifaddr** inet6_addr_lst ; 
 int /*<<< orphan*/  inet6addr_chain ; 
 int /*<<< orphan*/  ip6_del_rt (struct rt6_info*) ; 
 scalar_t__ ip6_route_lookup (struct net*,struct flowi*,int /*<<< orphan*/ ) ; 
 int ipv6_addr_hash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipv6_addr_prefix (struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_ifa_notify (int /*<<< orphan*/ ,struct inet6_ifaddr*) ; 
 scalar_t__ ipv6_prefix_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  rt6_remove_prefsrc (struct inet6_ifaddr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipv6_del_addr(struct inet6_ifaddr *ifp)
{
	struct inet6_ifaddr *ifa, **ifap;
	struct inet6_dev *idev = ifp->idev;
	int state;
	int hash;
	int deleted = 0, onlink = 0;
	unsigned long expires = jiffies;

	hash = ipv6_addr_hash(&ifp->addr);

	spin_lock_bh(&ifa_state_lock);
	state = ifp->dead;
	ifp->dead = INET6_IFADDR_STATE_DEAD;
	spin_unlock_bh(&ifa_state_lock);

	if (state == INET6_IFADDR_STATE_DEAD)
		goto out;


	write_lock_bh(&addrconf_hash_lock);
	for (ifap = &inet6_addr_lst[hash]; (ifa=*ifap) != NULL;
	     ifap = &ifa->lst_next) {
		if (ifa == ifp) {
			*ifap = ifa->lst_next;
			__in6_ifa_put(ifp);
			ifa->lst_next = NULL;
			break;
		}
	}
	write_unlock_bh(&addrconf_hash_lock);

	write_lock_bh(&idev->lock);
#ifdef CONFIG_IPV6_PRIVACY
	if (ifp->flags&IFA_F_TEMPORARY) {
		for (ifap = &idev->tempaddr_list; (ifa=*ifap) != NULL;
		     ifap = &ifa->tmp_next) {
			if (ifa == ifp) {
				*ifap = ifa->tmp_next;
				if (ifp->ifpub) {
					in6_ifa_put(ifp->ifpub);
					ifp->ifpub = NULL;
				}
				__in6_ifa_put(ifp);
				ifa->tmp_next = NULL;
				break;
			}
		}
	}
#endif

	for (ifap = &idev->addr_list; (ifa=*ifap) != NULL;) {
		if (ifa == ifp) {
			*ifap = ifa->if_next;
			__in6_ifa_put(ifp);
			ifa->if_next = NULL;
			if (!(ifp->flags & IFA_F_PERMANENT) || onlink > 0)
				break;
			deleted = 1;
			continue;
		} else if (ifp->flags & IFA_F_PERMANENT) {
			if (ipv6_prefix_equal(&ifa->addr, &ifp->addr,
					      ifp->prefix_len)) {
				if (ifa->flags & IFA_F_PERMANENT) {
					onlink = 1;
					if (deleted)
						break;
				} else {
					unsigned long lifetime;

					if (!onlink)
						onlink = -1;

					spin_lock(&ifa->lock);

					lifetime = addrconf_timeout_fixup(ifa->valid_lft, HZ);
					/*
					 * Note: Because this address is
					 * not permanent, lifetime <
					 * LONG_MAX / HZ here.
					 */
					if (time_before(expires,
							ifa->tstamp + lifetime * HZ))
						expires = ifa->tstamp + lifetime * HZ;
					spin_unlock(&ifa->lock);
				}
			}
		}
		ifap = &ifa->if_next;
	}
	write_unlock_bh(&idev->lock);

	addrconf_del_timer(ifp);

	ipv6_ifa_notify(RTM_DELADDR, ifp);

	atomic_notifier_call_chain(&inet6addr_chain, NETDEV_DOWN, ifp);

	/*
	 * Purge or update corresponding prefix
	 *
	 * 1) we don't purge prefix here if address was not permanent.
	 *    prefix is managed by its own lifetime.
	 * 2) if there're no addresses, delete prefix.
	 * 3) if there're still other permanent address(es),
	 *    corresponding prefix is still permanent.
	 * 4) otherwise, update prefix lifetime to the
	 *    longest valid lifetime among the corresponding
	 *    addresses on the device.
	 *    Note: subsequent RA will update lifetime.
	 *
	 * --yoshfuji
	 */
	if ((ifp->flags & IFA_F_PERMANENT) && onlink < 1) {
		struct in6_addr prefix;
		struct rt6_info *rt;
		struct net *net = dev_net(ifp->idev->dev);
		struct flowi fl = {};

		ipv6_addr_prefix(&prefix, &ifp->addr, ifp->prefix_len);
		fl.oif = ifp->idev->dev->ifindex;
		fl.nl_u.ip6_u.daddr = prefix;
		rt = (struct rt6_info *)ip6_route_lookup(net, &fl,
							 RT6_LOOKUP_F_IFACE);

		if (rt != net->ipv6.ip6_null_entry &&
		    addrconf_is_prefix_route(rt)) {
			if (onlink == 0) {
				ip6_del_rt(rt);
				rt = NULL;
			} else if (!(rt->rt6i_flags & RTF_EXPIRES)) {
				rt->rt6i_expires = expires;
				rt->rt6i_flags |= RTF_EXPIRES;
			}
		}
		dst_release(&rt->u.dst);
	}

	/* clean up prefsrc entries */
	rt6_remove_prefsrc(ifp);
out:
	in6_ifa_put(ifp);
}