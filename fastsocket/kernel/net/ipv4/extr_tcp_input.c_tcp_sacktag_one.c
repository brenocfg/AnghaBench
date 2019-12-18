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
typedef  int u8 ;
struct tcp_sock {int lost_out; int retrans_out; int sacked_out; int lost_cnt_hint; int fackets_out; struct sk_buff* lost_skb_hint; scalar_t__ frto_highmark; scalar_t__ snd_una; scalar_t__ undo_retrans; scalar_t__ undo_marker; } ;
struct tcp_sacktag_state {int fack_count; int /*<<< orphan*/  flag; void* reord; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int sacked; int /*<<< orphan*/  seq; int /*<<< orphan*/  end_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_DATA_SACKED ; 
 int /*<<< orphan*/  FLAG_ONLY_ORIG_SACKED ; 
 int TCPCB_LOST ; 
 int TCPCB_RETRANS ; 
 int TCPCB_SACKED_ACKED ; 
 int TCPCB_SACKED_RETRANS ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* min (int,void*) ; 
 int /*<<< orphan*/  tcp_highest_sack_seq (struct tcp_sock*) ; 
 int /*<<< orphan*/  tcp_is_fack (struct tcp_sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static u8 tcp_sacktag_one(struct sk_buff *skb, struct sock *sk,
			  struct tcp_sacktag_state *state,
			  int dup_sack, int pcount)
{
	struct tcp_sock *tp = tcp_sk(sk);
	u8 sacked = TCP_SKB_CB(skb)->sacked;
	int fack_count = state->fack_count;

	/* Account D-SACK for retransmitted packet. */
	if (dup_sack && (sacked & TCPCB_RETRANS)) {
		if (tp->undo_marker && tp->undo_retrans &&
		    after(TCP_SKB_CB(skb)->end_seq, tp->undo_marker))
			tp->undo_retrans--;
		if (sacked & TCPCB_SACKED_ACKED)
			state->reord = min(fack_count, state->reord);
	}

	/* Nothing to do; acked frame is about to be dropped (was ACKed). */
	if (!after(TCP_SKB_CB(skb)->end_seq, tp->snd_una))
		return sacked;

	if (!(sacked & TCPCB_SACKED_ACKED)) {
		if (sacked & TCPCB_SACKED_RETRANS) {
			/* If the segment is not tagged as lost,
			 * we do not clear RETRANS, believing
			 * that retransmission is still in flight.
			 */
			if (sacked & TCPCB_LOST) {
				sacked &= ~(TCPCB_LOST|TCPCB_SACKED_RETRANS);
				tp->lost_out -= pcount;
				tp->retrans_out -= pcount;
			}
		} else {
			if (!(sacked & TCPCB_RETRANS)) {
				/* New sack for not retransmitted frame,
				 * which was in hole. It is reordering.
				 */
				if (before(TCP_SKB_CB(skb)->seq,
					   tcp_highest_sack_seq(tp)))
					state->reord = min(fack_count,
							   state->reord);

				/* SACK enhanced F-RTO (RFC4138; Appendix B) */
				if (!after(TCP_SKB_CB(skb)->end_seq, tp->frto_highmark))
					state->flag |= FLAG_ONLY_ORIG_SACKED;
			}

			if (sacked & TCPCB_LOST) {
				sacked &= ~TCPCB_LOST;
				tp->lost_out -= pcount;
			}
		}

		sacked |= TCPCB_SACKED_ACKED;
		state->flag |= FLAG_DATA_SACKED;
		tp->sacked_out += pcount;

		fack_count += pcount;

		/* Lost marker hint past SACKed? Tweak RFC3517 cnt */
		if (!tcp_is_fack(tp) && (tp->lost_skb_hint != NULL) &&
		    before(TCP_SKB_CB(skb)->seq,
			   TCP_SKB_CB(tp->lost_skb_hint)->seq))
			tp->lost_cnt_hint += pcount;

		if (fack_count > tp->fackets_out)
			tp->fackets_out = fack_count;
	}

	/* D-SACK. We can detect redundant retransmission in S|R and plain R
	 * frames and clear it. undo_retrans is decreased above, L|R frames
	 * are accounted above as well.
	 */
	if (dup_sack && (sacked & TCPCB_SACKED_RETRANS)) {
		sacked &= ~TCPCB_SACKED_RETRANS;
		tp->retrans_out -= pcount;
	}

	return sacked;
}