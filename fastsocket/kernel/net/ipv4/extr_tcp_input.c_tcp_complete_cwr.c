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
struct tcp_sock {int /*<<< orphan*/  snd_cwnd_stamp; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  snd_cwnd; scalar_t__ undo_marker; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_ca_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_EVENT_COMPLETE_CWR ; 
 scalar_t__ TCP_CA_CWR ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_ca_event (struct sock*,int /*<<< orphan*/ ) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_stamp ; 

__attribute__((used)) static inline void tcp_complete_cwr(struct sock *sk)
{
	struct tcp_sock *tp = tcp_sk(sk);

	/* Do not moderate cwnd if it's already undone in cwr or recovery. */
	if (tp->undo_marker) {
		if (inet_csk(sk)->icsk_ca_state == TCP_CA_CWR)
			tp->snd_cwnd = min(tp->snd_cwnd, tp->snd_ssthresh);
		else /* PRR */
			tp->snd_cwnd = tp->snd_ssthresh;
		tp->snd_cwnd_stamp = tcp_time_stamp;
	}
	tcp_ca_event(sk, CA_EVENT_COMPLETE_CWR);
}