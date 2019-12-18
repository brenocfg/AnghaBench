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
struct sock {scalar_t__ sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct sk_buff* alloc_skb (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_set_owner_r (struct sk_buff*,struct sock*) ; 

struct sk_buff *sock_rmalloc(struct sock *sk, unsigned long size, int force,
			     gfp_t priority)
{
	if (force || atomic_read(&sk->sk_rmem_alloc) < sk->sk_rcvbuf) {
		struct sk_buff *skb = alloc_skb(size, priority);
		if (skb) {
			skb_set_owner_r(skb, sk);
			return skb;
		}
	}
	return NULL;
}