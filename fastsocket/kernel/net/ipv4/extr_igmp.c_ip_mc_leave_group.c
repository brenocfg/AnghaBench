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
typedef  scalar_t__ u32 ;
struct sock {int /*<<< orphan*/  sk_omem_alloc; } ;
struct net {int dummy; } ;
struct TYPE_8__ {scalar_t__ s_addr; } ;
struct TYPE_6__ {scalar_t__ s_addr; } ;
struct ip_mreqn {scalar_t__ imr_ifindex; TYPE_3__ imr_address; TYPE_1__ imr_multiaddr; } ;
struct TYPE_9__ {scalar_t__ s_addr; } ;
struct TYPE_7__ {scalar_t__ s_addr; } ;
struct TYPE_10__ {scalar_t__ imr_ifindex; TYPE_4__ imr_address; TYPE_2__ imr_multiaddr; } ;
struct ip_mc_socklist {int /*<<< orphan*/  rcu; struct ip_mc_socklist* next; TYPE_5__ multi; } ;
struct inet_sock {struct ip_mc_socklist* mc_list; } ;
struct in_device {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int ENODEV ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  ip_mc_dec_group (struct in_device*,scalar_t__) ; 
 struct in_device* ip_mc_find_dev (struct net*,struct ip_mreqn*) ; 
 int /*<<< orphan*/  ip_mc_leave_src (struct sock*,struct ip_mc_socklist*,struct in_device*) ; 
 int /*<<< orphan*/  ip_mc_socklist_reclaim ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct ip_mc_socklist*,struct ip_mc_socklist*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 struct net* sock_net (struct sock*) ; 

int ip_mc_leave_group(struct sock *sk, struct ip_mreqn *imr)
{
	struct inet_sock *inet = inet_sk(sk);
	struct ip_mc_socklist *iml, **imlp;
	struct in_device *in_dev;
	struct net *net = sock_net(sk);
	__be32 group = imr->imr_multiaddr.s_addr;
	u32 ifindex;
	int ret = -EADDRNOTAVAIL;

	rtnl_lock();
	in_dev = ip_mc_find_dev(net, imr);
	ifindex = imr->imr_ifindex;
	for (imlp = &inet->mc_list; (iml = *imlp) != NULL; imlp = &iml->next) {
		if (iml->multi.imr_multiaddr.s_addr != group)
			continue;
		if (ifindex) {
			if (iml->multi.imr_ifindex != ifindex)
				continue;
		} else if (imr->imr_address.s_addr && imr->imr_address.s_addr !=
				iml->multi.imr_address.s_addr)
			continue;

		(void) ip_mc_leave_src(sk, iml, in_dev);

		rcu_assign_pointer(*imlp, iml->next);

		if (in_dev)
			ip_mc_dec_group(in_dev, group);
		rtnl_unlock();
		/* decrease mem now to avoid the memleak warning */
		atomic_sub(sizeof(*iml), &sk->sk_omem_alloc);
		call_rcu(&iml->rcu, ip_mc_socklist_reclaim);
		return 0;
	}
	if (!in_dev)
		ret = -ENODEV;
	rtnl_unlock();
	return ret;
}