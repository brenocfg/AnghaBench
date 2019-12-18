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
typedef  int u32 ;
struct tcp_sock {int frto_counter; scalar_t__ snd_una; scalar_t__ high_seq; int snd_cwnd; scalar_t__ undo_marker; scalar_t__ frto_highmark; scalar_t__ snd_nxt; int /*<<< orphan*/  retrans_out; scalar_t__ undo_retrans; int /*<<< orphan*/  snd_ssthresh; int /*<<< orphan*/  prior_ssthresh; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct inet_connection_sock {int icsk_ca_state; TYPE_1__* icsk_ca_ops; int /*<<< orphan*/  icsk_retransmits; } ;
struct TYPE_4__ {int sacked; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* ssthresh ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CA_EVENT_FRTO ; 
 int TCPCB_RETRANS ; 
 int TCPCB_SACKED_RETRANS ; 
 int TCPF_CA_Loss ; 
 int TCPF_CA_Recovery ; 
 int TCP_CA_Disorder ; 
 int TCP_CA_Loss ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ after (scalar_t__,scalar_t__) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int min (int,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 
 int /*<<< orphan*/  tcp_ca_event (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_current_ssthresh (struct sock*) ; 
 scalar_t__ tcp_is_sackfrto (struct tcp_sock*) ; 
 scalar_t__ tcp_packets_in_flight (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_set_ca_state (struct sock*,int) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ tcp_skb_pcount (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_verify_left_out (struct tcp_sock*) ; 
 struct sk_buff* tcp_write_queue_head (struct sock*) ; 

void tcp_enter_frto(struct sock *sk)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	struct tcp_sock *tp = tcp_sk(sk);
	struct sk_buff *skb;

	if ((!tp->frto_counter && icsk->icsk_ca_state <= TCP_CA_Disorder) ||
	    tp->snd_una == tp->high_seq ||
	    ((icsk->icsk_ca_state == TCP_CA_Loss || tp->frto_counter) &&
	     !icsk->icsk_retransmits)) {
		tp->prior_ssthresh = tcp_current_ssthresh(sk);
		/* Our state is too optimistic in ssthresh() call because cwnd
		 * is not reduced until tcp_enter_frto_loss() when previous F-RTO
		 * recovery has not yet completed. Pattern would be this: RTO,
		 * Cumulative ACK, RTO (2xRTO for the same segment does not end
		 * up here twice).
		 * RFC4138 should be more specific on what to do, even though
		 * RTO is quite unlikely to occur after the first Cumulative ACK
		 * due to back-off and complexity of triggering events ...
		 */
		if (tp->frto_counter) {
			u32 stored_cwnd;
			stored_cwnd = tp->snd_cwnd;
			tp->snd_cwnd = 2;
			tp->snd_ssthresh = icsk->icsk_ca_ops->ssthresh(sk);
			tp->snd_cwnd = stored_cwnd;
		} else {
			tp->snd_ssthresh = icsk->icsk_ca_ops->ssthresh(sk);
		}
		/* ... in theory, cong.control module could do "any tricks" in
		 * ssthresh(), which means that ca_state, lost bits and lost_out
		 * counter would have to be faked before the call occurs. We
		 * consider that too expensive, unlikely and hacky, so modules
		 * using these in ssthresh() must deal these incompatibility
		 * issues if they receives CA_EVENT_FRTO and frto_counter != 0
		 */
		tcp_ca_event(sk, CA_EVENT_FRTO);
	}

	tp->undo_marker = tp->snd_una;
	tp->undo_retrans = 0;

	skb = tcp_write_queue_head(sk);
	if (TCP_SKB_CB(skb)->sacked & TCPCB_RETRANS)
		tp->undo_marker = 0;
	if (TCP_SKB_CB(skb)->sacked & TCPCB_SACKED_RETRANS) {
		TCP_SKB_CB(skb)->sacked &= ~TCPCB_SACKED_RETRANS;
		tp->retrans_out -= tcp_skb_pcount(skb);
	}
	tcp_verify_left_out(tp);

	/* Too bad if TCP was application limited */
	tp->snd_cwnd = min(tp->snd_cwnd, tcp_packets_in_flight(tp) + 1);

	/* Earlier loss recovery underway (see RFC4138; Appendix B).
	 * The last condition is necessary at least in tp->frto_counter case.
	 */
	if (tcp_is_sackfrto(tp) && (tp->frto_counter ||
	    ((1 << icsk->icsk_ca_state) & (TCPF_CA_Recovery|TCPF_CA_Loss))) &&
	    after(tp->high_seq, tp->snd_una)) {
		tp->frto_highmark = tp->high_seq;
	} else {
		tp->frto_highmark = tp->snd_nxt;
	}
	tcp_set_ca_state(sk, TCP_CA_Disorder);
	tp->high_seq = tp->snd_nxt;
	tp->frto_counter = 1;
}