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
struct socket {struct sock* sk; } ;
struct sockaddr_ll {scalar_t__ sll_family; scalar_t__ sll_protocol; scalar_t__ sll_ifindex; } ;
struct sockaddr {int dummy; } ;
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 scalar_t__ AF_PACKET ; 
 int EINVAL ; 
 int ENODEV ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int packet_do_bind (struct sock*,struct net_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pkt_sk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

__attribute__((used)) static int packet_bind(struct socket *sock, struct sockaddr *uaddr, int addr_len)
{
	struct sockaddr_ll *sll = (struct sockaddr_ll *)uaddr;
	struct sock *sk = sock->sk;
	struct net_device *dev = NULL;
	int err;


	/*
	 *	Check legality
	 */

	if (addr_len < sizeof(struct sockaddr_ll))
		return -EINVAL;
	if (sll->sll_family != AF_PACKET)
		return -EINVAL;

	if (sll->sll_ifindex) {
		err = -ENODEV;
		dev = dev_get_by_index(sock_net(sk), sll->sll_ifindex);
		if (dev == NULL)
			goto out;
	}
	err = packet_do_bind(sk, dev, sll->sll_protocol ? : pkt_sk(sk)->num);
	if (dev)
		dev_put(dev);

out:
	return err;
}