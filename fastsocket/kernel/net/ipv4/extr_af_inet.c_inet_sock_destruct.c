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
struct sock {scalar_t__ sk_type; scalar_t__ sk_state; int /*<<< orphan*/ * sk_rcv_dst; int /*<<< orphan*/ * sk_dst_cache; int /*<<< orphan*/  sk_forward_alloc; int /*<<< orphan*/  sk_wmem_queued; int /*<<< orphan*/  sk_wmem_alloc; int /*<<< orphan*/  sk_rmem_alloc; int /*<<< orphan*/  sk_error_queue; int /*<<< orphan*/  sk_receive_queue; } ;
struct inet_sock {int /*<<< orphan*/  opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ SOCK_STREAM ; 
 scalar_t__ TCP_CLOSE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dst_release (int /*<<< orphan*/ *) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_ip_options (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,struct sock*,...) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_mem_reclaim (struct sock*) ; 
 int /*<<< orphan*/  sk_refcnt_debug_dec (struct sock*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

void inet_sock_destruct(struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);

	__skb_queue_purge(&sk->sk_receive_queue);
	__skb_queue_purge(&sk->sk_error_queue);

	sk_mem_reclaim(sk);

	if (sk->sk_type == SOCK_STREAM && sk->sk_state != TCP_CLOSE) {
		pr_err("Attempt to release TCP socket in state %d %p\n",
		       sk->sk_state, sk);
		return;
	}
	if (!sock_flag(sk, SOCK_DEAD)) {
		pr_err("Attempt to release alive inet socket %p\n", sk);
		return;
	}

	WARN_ON(atomic_read(&sk->sk_rmem_alloc));
	WARN_ON(atomic_read(&sk->sk_wmem_alloc));
	WARN_ON(sk->sk_wmem_queued);
	WARN_ON(sk->sk_forward_alloc);

	kfree_ip_options(rcu_dereference(inet->opt));
	dst_release(sk->sk_dst_cache);
	if (sk->sk_rcv_dst) {
		//FPRINTK("Release dst 0x%p[%u] on socket 0x%p\n", sk->sk_rcv_dst, atomic_read(&sk->sk_rcv_dst->__refcnt), sk);
		dst_release(sk->sk_rcv_dst);
		sk->sk_rcv_dst = NULL;
	}
	sk_refcnt_debug_dec(sk);
}