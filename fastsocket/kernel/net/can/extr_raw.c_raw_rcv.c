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
struct sockaddr_can {int /*<<< orphan*/  can_ifindex; int /*<<< orphan*/  can_family; } ;
struct sock {int dummy; } ;
struct sk_buff {TYPE_1__* dev; scalar_t__ cb; struct sock* sk; } ;
struct raw_sock {int /*<<< orphan*/  recv_own_msgs; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CAN ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_can*,int /*<<< orphan*/ ,int) ; 
 struct raw_sock* raw_sk (struct sock*) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_queue_rcv_skb (struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void raw_rcv(struct sk_buff *skb, void *data)
{
	struct sock *sk = (struct sock *)data;
	struct raw_sock *ro = raw_sk(sk);
	struct sockaddr_can *addr;

	/* check the received tx sock reference */
	if (!ro->recv_own_msgs && skb->sk == sk)
		return;

	/* clone the given skb to be able to enqueue it into the rcv queue */
	skb = skb_clone(skb, GFP_ATOMIC);
	if (!skb)
		return;

	/*
	 *  Put the datagram to the queue so that raw_recvmsg() can
	 *  get it from there.  We need to pass the interface index to
	 *  raw_recvmsg().  We pass a whole struct sockaddr_can in skb->cb
	 *  containing the interface index.
	 */

	BUILD_BUG_ON(sizeof(skb->cb) < sizeof(struct sockaddr_can));
	addr = (struct sockaddr_can *)skb->cb;
	memset(addr, 0, sizeof(*addr));
	addr->can_family  = AF_CAN;
	addr->can_ifindex = skb->dev->ifindex;

	if (sock_queue_rcv_skb(sk, skb) < 0)
		kfree_skb(skb);
}