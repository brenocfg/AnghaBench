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
struct tcp_sock {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int MSG_MORE ; 
 int TCP_NAGLE_CORK ; 
 int /*<<< orphan*/  __tcp_push_pending_frames (struct sock*,int,int) ; 
 scalar_t__ forced_push (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_mark_push (struct tcp_sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_mark_urg (struct tcp_sock*,int,struct sk_buff*) ; 
 scalar_t__ tcp_send_head (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 struct sk_buff* tcp_write_queue_tail (struct sock*) ; 

__attribute__((used)) static inline void tcp_push(struct sock *sk, int flags, int mss_now,
			    int nonagle)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tcp_send_head(sk)) {
		struct sk_buff *skb = tcp_write_queue_tail(sk);
		if (!(flags & MSG_MORE) || forced_push(tp))
			tcp_mark_push(tp, skb);
		tcp_mark_urg(tp, flags, skb);
		__tcp_push_pending_frames(sk, mss_now,
					  (flags & MSG_MORE) ? TCP_NAGLE_CORK : nonagle);
	}
}