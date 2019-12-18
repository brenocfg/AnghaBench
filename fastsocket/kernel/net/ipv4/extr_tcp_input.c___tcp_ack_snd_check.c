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
struct tcp_sock {scalar_t__ rcv_nxt; scalar_t__ rcv_wup; scalar_t__ rcv_wnd; int /*<<< orphan*/  out_of_order_queue; } ;
struct sock {int dummy; } ;
struct TYPE_3__ {scalar_t__ rcv_mss; } ;
struct TYPE_4__ {TYPE_1__ icsk_ack; } ;

/* Variables and functions */
 scalar_t__ __tcp_select_window (struct sock*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 scalar_t__ skb_peek (int /*<<< orphan*/ *) ; 
 scalar_t__ tcp_in_quickack_mode (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_ack (struct sock*) ; 
 int /*<<< orphan*/  tcp_send_delayed_ack (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void __tcp_ack_snd_check(struct sock *sk, int ofo_possible)
{
	struct tcp_sock *tp = tcp_sk(sk);

	    /* More than one full frame received... */
	if (((tp->rcv_nxt - tp->rcv_wup) > inet_csk(sk)->icsk_ack.rcv_mss
	     /* ... and right edge of window advances far enough.
	      * (tcp_recvmsg() will send ACK otherwise). Or...
	      */
	     && __tcp_select_window(sk) >= tp->rcv_wnd) ||
	    /* We ACK each frame or... */
	    tcp_in_quickack_mode(sk) ||
	    /* We have out of order data. */
	    (ofo_possible && skb_peek(&tp->out_of_order_queue))) {
		/* Then ack it now */
		tcp_send_ack(sk);
	} else {
		/* Else, send delayed ack. */
		tcp_send_delayed_ack(sk);
	}
}