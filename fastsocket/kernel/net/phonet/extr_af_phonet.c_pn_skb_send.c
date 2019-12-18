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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sockaddr_pn {int dummy; } ;
struct sock {scalar_t__ sk_bound_dev_if; } ;
struct sk_buff {int dummy; } ;
struct pn_sock {int /*<<< orphan*/  sobject; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int EHOSTUNREACH ; 
 int IFF_UP ; 
 scalar_t__ PN_NO_ADDR ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ phonet_address_get (struct net_device*,scalar_t__) ; 
 struct net_device* phonet_device_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn_obj (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pn_object (scalar_t__,int /*<<< orphan*/ ) ; 
 int pn_send (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pn_sock* pn_sk (struct sock*) ; 
 scalar_t__ pn_sockaddr_get_addr (struct sockaddr_pn const*) ; 
 int /*<<< orphan*/  pn_sockaddr_get_object (struct sockaddr_pn const*) ; 
 int /*<<< orphan*/  pn_sockaddr_get_resource (struct sockaddr_pn const*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 

int pn_skb_send(struct sock *sk, struct sk_buff *skb,
		const struct sockaddr_pn *target)
{
	struct net_device *dev;
	struct pn_sock *pn = pn_sk(sk);
	int err;
	u16 src;
	u8 daddr = pn_sockaddr_get_addr(target), saddr = PN_NO_ADDR;

	err = -EHOSTUNREACH;
	if (sk->sk_bound_dev_if)
		dev = dev_get_by_index(sock_net(sk), sk->sk_bound_dev_if);
	else
		dev = phonet_device_get(sock_net(sk));
	if (!dev || !(dev->flags & IFF_UP))
		goto drop;

	saddr = phonet_address_get(dev, daddr);
	if (saddr == PN_NO_ADDR)
		goto drop;

	src = pn->sobject;
	if (!pn_addr(src))
		src = pn_object(saddr, pn_obj(src));

	err = pn_send(skb, dev, pn_sockaddr_get_object(target),
			src, pn_sockaddr_get_resource(target), 0);
	dev_put(dev);
	return err;

drop:
	kfree_skb(skb);
	if (dev)
		dev_put(dev);
	return err;
}