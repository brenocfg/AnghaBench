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
struct tcp_sock {int frto_counter; scalar_t__ undo_marker; scalar_t__ snd_cwnd; int /*<<< orphan*/  frto_highmark; int /*<<< orphan*/  snd_una; } ;
struct sock {int dummy; } ;
struct TYPE_2__ {scalar_t__ icsk_retransmits; } ;

/* Variables and functions */
 int FLAG_ANY_PROGRESS ; 
 int FLAG_DATA_ACKED ; 
 int FLAG_DATA_SACKED ; 
 int FLAG_FORWARD_PROGRESS ; 
 int FLAG_NONHEAD_RETRANS_ACKED ; 
 int FLAG_NOT_DUP ; 
 int FLAG_ONLY_ORIG_SACKED ; 
 int FLAG_RETRANS_DATA_ACKED ; 
 int /*<<< orphan*/  LINUX_MIB_TCPSPURIOUSRTOS ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int sysctl_tcp_frto_response ; 
 int /*<<< orphan*/  tcp_conservative_spur_to_response (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_enter_frto_loss (struct sock*,int,int) ; 
 int /*<<< orphan*/  tcp_is_sackfrto (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_may_send_now (struct sock*) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_ratehalving_spur_to_response (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_undo_spur_to_response (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 

__attribute__((used)) static int tcp_process_frto(struct sock *sk, int flag)
{
	struct tcp_sock *tp = tcp_sk(sk);

	tcp_verify_left_out(tp);

	/* Duplicate the behavior from Loss state (fastretrans_alert) */
	if (flag & FLAG_DATA_ACKED)
		inet_csk(sk)->icsk_retransmits = 0;

	if ((flag & FLAG_NONHEAD_RETRANS_ACKED) ||
	    ((tp->frto_counter >= 2) && (flag & FLAG_RETRANS_DATA_ACKED)))
		tp->undo_marker = 0;

	if (!before(tp->snd_una, tp->frto_highmark)) {
		tcp_enter_frto_loss(sk, (tp->frto_counter == 1 ? 2 : 3), flag);
		return 1;
	}

	if (!tcp_is_sackfrto(tp)) {
		/* RFC4138 shortcoming in step 2; should also have case c):
		 * ACK isn't duplicate nor advances window, e.g., opposite dir
		 * data, winupdate
		 */
		if (!(flag & FLAG_ANY_PROGRESS) && (flag & FLAG_NOT_DUP))
			return 1;

		if (!(flag & FLAG_DATA_ACKED)) {
			tcp_enter_frto_loss(sk, (tp->frto_counter == 1 ? 0 : 3),
					    flag);
			return 1;
		}
	} else {
		if (!(flag & FLAG_DATA_ACKED) && (tp->frto_counter == 1)) {
			if (!tcp_packets_in_flight(tp)) {
				tcp_enter_frto_loss(sk, 2, flag);
				return true;
			}

			/* Prevent sending of new data. */
			tp->snd_cwnd = min(tp->snd_cwnd,
					   tcp_packets_in_flight(tp));
			return 1;
		}

		if ((tp->frto_counter >= 2) &&
		    (!(flag & FLAG_FORWARD_PROGRESS) ||
		     ((flag & FLAG_DATA_SACKED) &&
		      !(flag & FLAG_ONLY_ORIG_SACKED)))) {
			/* RFC4138 shortcoming (see comment above) */
			if (!(flag & FLAG_FORWARD_PROGRESS) &&
			    (flag & FLAG_NOT_DUP))
				return 1;

			tcp_enter_frto_loss(sk, 3, flag);
			return 1;
		}
	}

	if (tp->frto_counter == 1) {
		/* tcp_may_send_now needs to see updated state */
		tp->snd_cwnd = tcp_packets_in_flight(tp) + 2;
		tp->frto_counter = 2;

		if (!tcp_may_send_now(sk))
			tcp_enter_frto_loss(sk, 2, flag);

		return 1;
	} else {
		switch (sysctl_tcp_frto_response) {
		case 2:
			tcp_undo_spur_to_response(sk, flag);
			break;
		case 1:
			tcp_conservative_spur_to_response(tp);
			break;
		default:
			tcp_ratehalving_spur_to_response(sk);
			break;
		}
		tp->frto_counter = 0;
		tp->undo_marker = 0;
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPSPURIOUSRTOS);
	}
	return 0;
}