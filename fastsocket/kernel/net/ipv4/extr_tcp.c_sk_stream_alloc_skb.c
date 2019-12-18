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
struct sock {TYPE_1__* sk_prot; } ;
struct sk_buff {int /*<<< orphan*/  truesize; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* enter_memory_pressure ) (struct sock*) ;scalar_t__ max_header; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  SOCK_SKB_POOL ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 struct sk_buff* alloc_pool_skb_fclone (scalar_t__,int /*<<< orphan*/ ) ; 
 struct sk_buff* alloc_skb_fclone (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_stream_moderate_sndbuf (struct sock*) ; 
 scalar_t__ sk_wmem_schedule (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 scalar_t__ skb_tailroom (struct sk_buff*) ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

struct sk_buff *sk_stream_alloc_skb(struct sock *sk, int size, gfp_t gfp)
{
	struct sk_buff *skb;

	/* The TCP header must be at least 32-bit aligned.  */
	size = ALIGN(size, 4);

	if (sock_flag(sk, SOCK_SKB_POOL))
		skb = alloc_pool_skb_fclone(size + sk->sk_prot->max_header, gfp);
	else
		skb = alloc_skb_fclone(size + sk->sk_prot->max_header, gfp);
	if (skb) {
		if (sk_wmem_schedule(sk, skb->truesize)) {
			/*
			 * Make sure that we have exactly size bytes
			 * available to the caller, no more, no less.
			 */
			skb_reserve(skb, skb_tailroom(skb) - size);
			return skb;
		}
		__kfree_skb(skb);
	} else {
		sk->sk_prot->enter_memory_pressure(sk);
		sk_stream_moderate_sndbuf(sk);
	}
	return NULL;
}