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
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ipv6_pinfo {struct ipv6_mc_socklist* ipv6_mc_list; } ;
struct ipv6_mc_socklist {int /*<<< orphan*/  addr; int /*<<< orphan*/  ifindex; struct ipv6_mc_socklist* next; } ;
struct inet6_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipv6_dev_mc_dec (struct inet6_dev*,int /*<<< orphan*/ *) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct inet6_dev* in6_dev_get (struct net_device*) ; 
 int /*<<< orphan*/  in6_dev_put (struct inet6_dev*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 int /*<<< orphan*/  ip6_mc_leave_src (struct sock*,struct ipv6_mc_socklist*,struct inet6_dev*) ; 
 int /*<<< orphan*/  ipv6_sk_mc_lock ; 
 int /*<<< orphan*/  sock_kfree_s (struct sock*,struct ipv6_mc_socklist*,int) ; 
 struct net* sock_net (struct sock*) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void ipv6_sock_mc_close(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct ipv6_mc_socklist *mc_lst;
	struct net *net = sock_net(sk);

	write_lock_bh(&ipv6_sk_mc_lock);
	while ((mc_lst = np->ipv6_mc_list) != NULL) {
		struct net_device *dev;

		np->ipv6_mc_list = mc_lst->next;
		write_unlock_bh(&ipv6_sk_mc_lock);

		dev = dev_get_by_index(net, mc_lst->ifindex);
		if (dev) {
			struct inet6_dev *idev = in6_dev_get(dev);

			(void) ip6_mc_leave_src(sk, mc_lst, idev);
			if (idev) {
				__ipv6_dev_mc_dec(idev, &mc_lst->addr);
				in6_dev_put(idev);
			}
			dev_put(dev);
		} else
			(void) ip6_mc_leave_src(sk, mc_lst, NULL);

		sock_kfree_s(sk, mc_lst, sizeof(*mc_lst));

		write_lock_bh(&ipv6_sk_mc_lock);
	}
	write_unlock_bh(&ipv6_sk_mc_lock);
}