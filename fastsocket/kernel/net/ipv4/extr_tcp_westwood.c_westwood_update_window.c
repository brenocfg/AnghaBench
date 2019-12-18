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
struct westwood {scalar_t__ rtt_win_sx; scalar_t__ bk; scalar_t__ rtt; scalar_t__ first_ack; int /*<<< orphan*/  snd_una; } ;
struct sock {int dummy; } ;
typedef  scalar_t__ s32 ;
struct TYPE_2__ {int /*<<< orphan*/  snd_una; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_WESTWOOD_RTT_MIN ; 
 struct westwood* inet_csk_ca (struct sock*) ; 
 scalar_t__ max_t (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_time_stamp ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  westwood_filter (struct westwood*,scalar_t__) ; 

__attribute__((used)) static void westwood_update_window(struct sock *sk)
{
	struct westwood *w = inet_csk_ca(sk);
	s32 delta = tcp_time_stamp - w->rtt_win_sx;

	/* Initialize w->snd_una with the first acked sequence number in order
	 * to fix mismatch between tp->snd_una and w->snd_una for the first
	 * bandwidth sample
	 */
	if (w->first_ack) {
		w->snd_una = tcp_sk(sk)->snd_una;
		w->first_ack = 0;
	}

	/*
	 * See if a RTT-window has passed.
	 * Be careful since if RTT is less than
	 * 50ms we don't filter but we continue 'building the sample'.
	 * This minimum limit was chosen since an estimation on small
	 * time intervals is better to avoid...
	 * Obviously on a LAN we reasonably will always have
	 * right_bound = left_bound + WESTWOOD_RTT_MIN
	 */
	if (w->rtt && delta > max_t(u32, w->rtt, TCP_WESTWOOD_RTT_MIN)) {
		westwood_filter(w, delta);

		w->bk = 0;
		w->rtt_win_sx = tcp_time_stamp;
	}
}