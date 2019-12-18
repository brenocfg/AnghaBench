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
struct tcp_sock {int fackets_out; int reordering; int sacked_out; } ;
struct sock {int dummy; } ;

/* Variables and functions */
 scalar_t__ tcp_is_fack (struct tcp_sock*) ; 
 scalar_t__ tcp_is_reno (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_mark_head_lost (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_timeout_skbs (struct sock*) ; 

__attribute__((used)) static void tcp_update_scoreboard(struct sock *sk, int fast_rexmit)
{
	struct tcp_sock *tp = tcp_sk(sk);

	if (tcp_is_reno(tp)) {
		tcp_mark_head_lost(sk, 1);
	} else if (tcp_is_fack(tp)) {
		int lost = tp->fackets_out - tp->reordering;
		if (lost <= 0)
			lost = 1;
		tcp_mark_head_lost(sk, lost);
	} else {
		int sacked_upto = tp->sacked_out - tp->reordering;
		if (sacked_upto < fast_rexmit)
			sacked_upto = fast_rexmit;
		tcp_mark_head_lost(sk, sacked_upto);
	}

	tcp_timeout_skbs(sk);
}