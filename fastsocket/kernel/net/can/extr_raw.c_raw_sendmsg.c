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
struct socket {struct sock* sk; } ;
struct sockaddr_can {scalar_t__ can_family; int can_ifindex; } ;
struct sock {int dummy; } ;
struct sk_buff {struct sock* sk; struct net_device* dev; } ;
struct raw_sock {int ifindex; int /*<<< orphan*/  loopback; } ;
struct net_device {int dummy; } ;
struct msghdr {int msg_flags; int /*<<< orphan*/  msg_iov; scalar_t__ msg_name; } ;
struct kiocb {int dummy; } ;
struct can_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_CAN ; 
 int EINVAL ; 
 int ENXIO ; 
 int MSG_DONTWAIT ; 
 int can_send (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int memcpy_fromiovec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct raw_sock* raw_sk (struct sock*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_tx (struct sk_buff*) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,size_t,int,int*) ; 
 int sock_tx_timestamp (struct msghdr*,struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raw_sendmsg(struct kiocb *iocb, struct socket *sock,
		       struct msghdr *msg, size_t size)
{
	struct sock *sk = sock->sk;
	struct raw_sock *ro = raw_sk(sk);
	struct sk_buff *skb;
	struct net_device *dev;
	int ifindex;
	int err;

	if (msg->msg_name) {
		struct sockaddr_can *addr =
			(struct sockaddr_can *)msg->msg_name;

		if (addr->can_family != AF_CAN)
			return -EINVAL;

		ifindex = addr->can_ifindex;
	} else
		ifindex = ro->ifindex;

	if (size != sizeof(struct can_frame))
		return -EINVAL;

	dev = dev_get_by_index(&init_net, ifindex);
	if (!dev)
		return -ENXIO;

	skb = sock_alloc_send_skb(sk, size, msg->msg_flags & MSG_DONTWAIT,
				  &err);
	if (!skb)
		goto put_dev;

	err = memcpy_fromiovec(skb_put(skb, size), msg->msg_iov, size);
	if (err < 0)
		goto free_skb;
	err = sock_tx_timestamp(msg, sk, skb_tx(skb));
	if (err < 0)
		goto free_skb;
	skb->dev = dev;
	skb->sk  = sk;

	err = can_send(skb, ro->loopback);

	dev_put(dev);

	if (err)
		goto send_failed;

	return size;

free_skb:
	kfree_skb(skb);
put_dev:
	dev_put(dev);
send_failed:
	return err;
}