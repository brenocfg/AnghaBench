#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  prequeue; } ;
struct tcp_sock {TYPE_1__ ucopy; int /*<<< orphan*/ * md5sig_info; int /*<<< orphan*/  out_of_order_queue; } ;
struct sock {int /*<<< orphan*/ * sk_sndmsg_page; int /*<<< orphan*/  sk_async_wait_queue; } ;
struct TYPE_4__ {scalar_t__ icsk_bind_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_purge (int /*<<< orphan*/ *) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_put_port (struct sock*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_cleanup_congestion_control (struct sock*) ; 
 int /*<<< orphan*/  tcp_clear_xmit_timers (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sockets_allocated ; 
 int /*<<< orphan*/  tcp_v4_clear_md5_list (struct sock*) ; 
 int /*<<< orphan*/  tcp_write_queue_purge (struct sock*) ; 

void tcp_v4_destroy_sock(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	tcp_clear_xmit_timers(sk);

	tcp_cleanup_congestion_control(sk);

	/* Cleanup up the write buffer. */
	tcp_write_queue_purge(sk);

	/* Cleans up our, hopefully empty, out_of_order_queue. */
	__skb_queue_purge(&tp->out_of_order_queue);

#ifdef CONFIG_TCP_MD5SIG
	/* Clean up the MD5 key list, if any */
	if (tp->md5sig_info) {
		tcp_v4_clear_md5_list(sk);
		kfree(tp->md5sig_info);
		tp->md5sig_info = NULL;
	}
#endif

#ifdef CONFIG_NET_DMA
	/* Cleans up our sk_async_wait_queue */
	__skb_queue_purge(&sk->sk_async_wait_queue);
#endif

	/* Clean prequeue, it must be empty really */
	__skb_queue_purge(&tp->ucopy.prequeue);

	/* Clean up a referenced TCP bind bucket. */
	if (inet_csk(sk)->icsk_bind_hash)
		inet_put_port(sk);

	/*
	 * If sendmsg cached page exists, toss it.
	 */
	if (sk->sk_sndmsg_page) {
		__free_page(sk->sk_sndmsg_page);
		sk->sk_sndmsg_page = NULL;
	}

	percpu_counter_dec(&tcp_sockets_allocated);
}