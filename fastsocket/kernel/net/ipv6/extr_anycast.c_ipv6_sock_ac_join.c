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
struct sock {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dst; } ;
struct rt6_info {TYPE_3__ u; struct net_device* rt6i_dev; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_6__ {TYPE_1__* devconf_all; } ;
struct net {TYPE_2__ ipv6; } ;
struct ipv6_pinfo {struct ipv6_ac_socklist* ipv6_ac_list; } ;
struct ipv6_ac_socklist {struct ipv6_ac_socklist* acl_next; int /*<<< orphan*/  acl_ifindex; int /*<<< orphan*/  acl_addr; } ;
struct TYPE_8__ {int /*<<< orphan*/  forwarding; } ;
struct inet6_dev {TYPE_4__ cnf; } ;
struct in6_addr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  forwarding; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EADDRNOTAVAIL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_LOOPBACK ; 
 int IFF_UP ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_flags (struct net*,int,int) ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ipv6_addr_copy (int /*<<< orphan*/ *,struct in6_addr*) ; 
 scalar_t__ ipv6_addr_is_multicast (struct in6_addr*) ; 
 scalar_t__ ipv6_chk_addr (struct net*,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipv6_chk_prefix (struct in6_addr*,struct net_device*) ; 
 int ipv6_dev_ac_inc (struct net_device*,struct in6_addr*) ; 
 int /*<<< orphan*/  ipv6_sk_ac_lock ; 
 struct rt6_info* rt6_lookup (struct net*,struct in6_addr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_ac_socklist*,int) ; 
 struct ipv6_ac_socklist* sock_kmalloc (struct sock*,int,int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int ipv6_sock_ac_join(struct sock *sk, int ifindex, struct in6_addr *addr)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct net_device *dev = NULL;
	struct inet6_dev *idev;
	struct ipv6_ac_socklist *pac;
	struct net *net = sock_net(sk);
	int	ishost = !net->ipv6.devconf_all->forwarding;
	int	err = 0;

	if (!capable(CAP_NET_ADMIN))
		return -EPERM;
	if (ipv6_addr_is_multicast(addr))
		return -EINVAL;
	if (ipv6_chk_addr(net, addr, NULL, 0))
		return -EINVAL;

	pac = sock_kmalloc(sk, sizeof(struct ipv6_ac_socklist), GFP_KERNEL);
	if (pac == NULL)
		return -ENOMEM;
	pac->acl_next = NULL;
	ipv6_addr_copy(&pac->acl_addr, addr);

	if (ifindex == 0) {
		struct rt6_info *rt;

		rt = rt6_lookup(net, addr, NULL, 0, 0);
		if (rt) {
			dev = rt->rt6i_dev;
			dev_hold(dev);
			dst_release(&rt->u.dst);
		} else if (ishost) {
			err = -EADDRNOTAVAIL;
			goto out_free_pac;
		} else {
			/* router, no matching interface: just pick one */

			dev = dev_get_by_flags(net, IFF_UP, IFF_UP|IFF_LOOPBACK);
		}
	} else
		dev = dev_get_by_index(net, ifindex);

	if (dev == NULL) {
		err = -ENODEV;
		goto out_free_pac;
	}

	idev = in6_dev_get(dev);
	if (!idev) {
		if (ifindex)
			err = -ENODEV;
		else
			err = -EADDRNOTAVAIL;
		goto out_dev_put;
	}
	/* reset ishost, now that we have a specific device */
	ishost = !idev->cnf.forwarding;
	in6_dev_put(idev);

	pac->acl_ifindex = dev->ifindex;

	/* XXX
	 * For hosts, allow link-local or matching prefix anycasts.
	 * This obviates the need for propagating anycast routes while
	 * still allowing some non-router anycast participation.
	 */
	if (!ipv6_chk_prefix(addr, dev)) {
		if (ishost)
			err = -EADDRNOTAVAIL;
		if (err)
			goto out_dev_put;
	}

	err = ipv6_dev_ac_inc(dev, addr);
	if (err)
		goto out_dev_put;

	write_lock_bh(&ipv6_sk_ac_lock);
	pac->acl_next = np->ipv6_ac_list;
	np->ipv6_ac_list = pac;
	write_unlock_bh(&ipv6_sk_ac_lock);

	dev_put(dev);

	return 0;

out_dev_put:
	dev_put(dev);
out_free_pac:
	sock_kfree_s(sk, pac, sizeof(*pac));
	return err;
}