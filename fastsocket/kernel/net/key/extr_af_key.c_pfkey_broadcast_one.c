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
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  users; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  sock_hold (struct sock*) ; 
 int /*<<< orphan*/  sock_put (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pfkey_broadcast_one(struct sk_buff *skb, struct sk_buff **skb2,
			       gfp_t allocation, struct sock *sk)
{
	int err = -ENOBUFS;

	sock_hold(sk);
	if (*skb2 == NULL) {
		if (atomic_read(&skb->users) != 1) {
			*skb2 = skb_clone(skb, allocation);
		} else {
			*skb2 = skb;
			atomic_inc(&skb->users);
		}
	}
	if (*skb2 != NULL) {
		if (atomic_read(&sk->sk_rmem_alloc) <= sk->sk_rcvbuf) {
			skb_orphan(*skb2);
			skb_set_owner_r(*skb2, sk);
			skb_queue_tail(&sk->sk_receive_queue, *skb2);
			sk->sk_data_ready(sk, (*skb2)->len);
			*skb2 = NULL;
			err = 0;
		}
	}
	sock_put(sk);
	return err;
}