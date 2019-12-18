#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  probe_seq_start; } ;
struct tcp_sock {scalar_t__ reordering; scalar_t__ fackets_out; scalar_t__ retrans_out; scalar_t__ undo_retrans; int prr_delivered; int /*<<< orphan*/  prr_out; int /*<<< orphan*/  snd_cwnd; int /*<<< orphan*/  prior_cwnd; int /*<<< orphan*/  snd_cwnd_cnt; int /*<<< orphan*/  bytes_acked; int /*<<< orphan*/  snd_ssthresh; scalar_t__ prior_ssthresh; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  undo_marker; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  high_seq; TYPE_2__ mtu_probe; scalar_t__ retrans_stamp; scalar_t__ sacked_out; int /*<<< orphan*/  packets_out; } ;
struct sock {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  probe_size; } ;
struct inet_connection_sock {int const icsk_ca_state; TYPE_3__* icsk_ca_ops; TYPE_1__ icsk_mtup; int /*<<< orphan*/  icsk_retransmits; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ssthresh ) (struct sock*) ;} ;

/* Variables and functions */
 int FLAG_DATA_ACKED ; 
 int FLAG_DATA_LOST ; 
 int FLAG_DATA_SACKED ; 
 int FLAG_ECE ; 
 int FLAG_SND_UNA_ADVANCED ; 
 int LINUX_MIB_TCPLOSS ; 
 int LINUX_MIB_TCPRENORECOVERY ; 
 int LINUX_MIB_TCPSACKRECOVERY ; 
 int /*<<< orphan*/  NET_INC_STATS_BH (int /*<<< orphan*/ ,int) ; 
#define  TCP_CA_CWR 130 
 int const TCP_CA_Disorder ; 
#define  TCP_CA_Loss 129 
 int const TCP_CA_Open ; 
#define  TCP_CA_Recovery 128 
 int /*<<< orphan*/  TCP_ECN_queue_cwr (struct tcp_sock*) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  tcp_add_reno_sack (struct sock*) ; 
 scalar_t__ tcp_check_sack_reneging (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_complete_cwr (struct sock*) ; 
 scalar_t__ tcp_current_ssthresh (struct sock*) ; 
 scalar_t__ tcp_fackets_out (struct tcp_sock*) ; 
 scalar_t__ tcp_head_timedout (struct sock*) ; 
 scalar_t__ tcp_is_fack (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_is_reno (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_mark_head_lost (struct sock*,scalar_t__) ; 
 int /*<<< orphan*/  tcp_moderate_cwnd (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_mtup_probe_failed (struct sock*) ; 
 int /*<<< orphan*/  tcp_reset_reno_sack (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int const) ; 
 int /*<<< orphan*/  tcp_simple_retransmit (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_time_to_recover (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_to_open (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_try_undo_dsack (struct sock*) ; 
 int /*<<< orphan*/  tcp_try_undo_loss (struct sock*) ; 
 int tcp_try_undo_partial (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_try_undo_recovery (struct sock*) ; 
 int /*<<< orphan*/  tcp_update_cwnd_in_recovery (struct sock*,int,int,int) ; 
 int /*<<< orphan*/  tcp_update_scoreboard (struct sock*,int) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_xmit_retransmit_queue (struct sock*) ; 

__attribute__((used)) static void tcp_fastretrans_alert(struct sock *sk, int pkts_acked,
				  int newly_acked_sacked, bool is_dupack,
				  int flag)
{
	struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	int do_lost = is_dupack || ((flag & FLAG_DATA_SACKED) &&
				    (tcp_fackets_out(tp) > tp->reordering));
	int fast_rexmit = 0, mib_idx;

	if (WARN_ON(!tp->packets_out && tp->sacked_out))
		tp->sacked_out = 0;
	if (WARN_ON(!tp->sacked_out && tp->fackets_out))
		tp->fackets_out = 0;

	/* Now state machine starts.
	 * A. ECE, hence prohibit cwnd undoing, the reduction is required. */
	if (flag & FLAG_ECE)
		tp->prior_ssthresh = 0;

	/* B. In all the states check for reneging SACKs. */
	if (tcp_check_sack_reneging(sk, flag))
		return;

	/* C. Process data loss notification, provided it is valid. */
	if (tcp_is_fack(tp) && (flag & FLAG_DATA_LOST) &&
	    before(tp->snd_una, tp->high_seq) &&
	    icsk->icsk_ca_state != TCP_CA_Open &&
	    tp->fackets_out > tp->reordering) {
		tcp_mark_head_lost(sk, tp->fackets_out - tp->reordering);
		NET_INC_STATS_BH(sock_net(sk), LINUX_MIB_TCPLOSS);
	}

	/* D. Check consistency of the current state. */
	tcp_verify_left_out(tp);

	/* E. Check state exit conditions. State can be terminated
	 *    when high_seq is ACKed. */
	if (icsk->icsk_ca_state == TCP_CA_Open) {
		WARN_ON(tp->retrans_out != 0);
		tp->retrans_stamp = 0;
	} else if (!before(tp->snd_una, tp->high_seq)) {
		switch (icsk->icsk_ca_state) {
		case TCP_CA_Loss:
			icsk->icsk_retransmits = 0;
			if (tcp_try_undo_recovery(sk))
				return;
			break;

		case TCP_CA_CWR:
			/* CWR is to be held something *above* high_seq
			 * is ACKed for CWR bit to reach receiver. */
			if (tp->snd_una != tp->high_seq) {
				tcp_complete_cwr(sk);
				tcp_set_ca_state(sk, TCP_CA_Open);
			}
			break;

		case TCP_CA_Recovery:
			if (tcp_is_reno(tp))
				tcp_reset_reno_sack(tp);
			if (tcp_try_undo_recovery(sk))
				return;
			tcp_complete_cwr(sk);
			break;
		}
	}

	/* F. Process state. */
	switch (icsk->icsk_ca_state) {
	case TCP_CA_Recovery:
		if (!(flag & FLAG_SND_UNA_ADVANCED)) {
			if (tcp_is_reno(tp) && is_dupack)
				tcp_add_reno_sack(sk);
		} else
			do_lost = tcp_try_undo_partial(sk, pkts_acked);
		break;
	case TCP_CA_Loss:
		if (flag & FLAG_DATA_ACKED)
			icsk->icsk_retransmits = 0;
		if (tcp_is_reno(tp) && flag & FLAG_SND_UNA_ADVANCED)
			tcp_reset_reno_sack(tp);
		if (!tcp_try_undo_loss(sk)) {
			tcp_moderate_cwnd(tp);
			tcp_xmit_retransmit_queue(sk);
			return;
		}
		if (icsk->icsk_ca_state != TCP_CA_Open)
			return;
		/* Loss is undone; fall through to processing in Open state. */
	default:
		if (tcp_is_reno(tp)) {
			if (flag & FLAG_SND_UNA_ADVANCED)
				tcp_reset_reno_sack(tp);
			if (is_dupack)
				tcp_add_reno_sack(sk);
		}

		if (icsk->icsk_ca_state <= TCP_CA_Disorder)
			tcp_try_undo_dsack(sk);

		if (!tcp_time_to_recover(sk)) {
			tcp_try_to_open(sk, flag);
			return;
		}

		/* MTU probe failure: don't reduce cwnd */
		if (icsk->icsk_ca_state < TCP_CA_CWR &&
		    icsk->icsk_mtup.probe_size &&
		    tp->snd_una == tp->mtu_probe.probe_seq_start) {
			tcp_mtup_probe_failed(sk);
			/* Restores the reduction we did in tcp_mtup_probe() */
			tp->snd_cwnd++;
			tcp_simple_retransmit(sk);
			return;
		}

		/* Otherwise enter Recovery state */

		if (tcp_is_reno(tp))
			mib_idx = LINUX_MIB_TCPRENORECOVERY;
		else
			mib_idx = LINUX_MIB_TCPSACKRECOVERY;

		NET_INC_STATS_BH(sock_net(sk), mib_idx);

		tp->high_seq = tp->snd_nxt;
		tp->prior_ssthresh = 0;
		tp->undo_marker = tp->snd_una;
		tp->undo_retrans = tp->retrans_out;

		if (icsk->icsk_ca_state < TCP_CA_CWR) {
			if (!(flag & FLAG_ECE))
				tp->prior_ssthresh = tcp_current_ssthresh(sk);
			tp->snd_ssthresh = icsk->icsk_ca_ops->ssthresh(sk);
			TCP_ECN_queue_cwr(tp);
		}

		tp->bytes_acked = 0;
		tp->snd_cwnd_cnt = 0;
		tp->prior_cwnd = tp->snd_cwnd;
		tp->prr_delivered = 0;
		tp->prr_out = 0;
		tcp_set_ca_state(sk, TCP_CA_Recovery);
		fast_rexmit = 1;
	}

	if (do_lost || (tcp_is_fack(tp) && tcp_head_timedout(sk)))
		tcp_update_scoreboard(sk, fast_rexmit);
	tp->prr_delivered += newly_acked_sacked;
	tcp_update_cwnd_in_recovery(sk, newly_acked_sacked, fast_rexmit, flag);
	tcp_xmit_retransmit_queue(sk);
}