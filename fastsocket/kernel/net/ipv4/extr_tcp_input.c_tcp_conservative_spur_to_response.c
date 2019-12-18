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
struct tcp_sock {scalar_t__ bytes_acked; scalar_t__ snd_cwnd_cnt; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_cwnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_ECN_queue_cwr (struct tcp_sock*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_moderate_cwnd (struct tcp_sock*) ; 

__attribute__((used)) static void tcp_conservative_spur_to_response(struct tcp_sock *tp)
{
	tp->snd_cwnd = min(tp->snd_cwnd, tp->snd_ssthresh);
	tp->snd_cwnd_cnt = 0;
	tp->bytes_acked = 0;
	TCP_ECN_queue_cwr(tp);
	tcp_moderate_cwnd(tp);
}