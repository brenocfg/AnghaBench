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
struct sock {scalar_t__ sk_bound_dev_if; } ;
struct net_device {scalar_t__ ifindex; } ;
struct ip_mreqn {scalar_t__ imr_ifindex; int /*<<< orphan*/  imr_multiaddr; } ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct net_device* __dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_net ; 
 int ip_mc_join_group (struct sock*,struct ip_mreqn*) ; 
 int /*<<< orphan*/  lock_sock (struct sock*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct in_addr*,int) ; 
 int /*<<< orphan*/  memset (struct ip_mreqn*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_sock (struct sock*) ; 

__attribute__((used)) static int
join_mcast_group(struct sock *sk, struct in_addr *addr, char *ifname)
{
	struct ip_mreqn mreq;
	struct net_device *dev;
	int ret;

	memset(&mreq, 0, sizeof(mreq));
	memcpy(&mreq.imr_multiaddr, addr, sizeof(struct in_addr));

	if ((dev = __dev_get_by_name(&init_net, ifname)) == NULL)
		return -ENODEV;
	if (sk->sk_bound_dev_if && dev->ifindex != sk->sk_bound_dev_if)
		return -EINVAL;

	mreq.imr_ifindex = dev->ifindex;

	lock_sock(sk);
	ret = ip_mc_join_group(sk, &mreq);
	release_sock(sk);

	return ret;
}