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
struct tcp_sock {scalar_t__ rcv_ssthresh; scalar_t__ window_clamp; int advmss; } ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  truesize; } ;
struct TYPE_3__ {int quick; } ;
struct TYPE_4__ {TYPE_1__ icsk_ack; } ;

/* Variables and functions */
 int __tcp_grow_window (struct sock*,struct sk_buff*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tcp_memory_pressure ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int tcp_space (struct sock*) ; 
 scalar_t__ tcp_win_from_space (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_grow_window(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);

	/* Check #1 */
	if (tp->rcv_ssthresh < tp->window_clamp &&
	    (int)tp->rcv_ssthresh < tcp_space(sk) &&
	    !tcp_memory_pressure) {
		int incr;

		/* Check #2. Increase window, if skb with such overhead
		 * will fit to rcvbuf in future.
		 */
		if (tcp_win_from_space(skb->truesize) <= skb->len)
			incr = 2 * tp->advmss;
		else
			incr = __tcp_grow_window(sk, skb);

		if (incr) {
			tp->rcv_ssthresh = min(tp->rcv_ssthresh + incr,
					       tp->window_clamp);
			inet_csk(sk)->icsk_ack.quick |= 1;
		}
	}
}