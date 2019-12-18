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
typedef  scalar_t__ u8 ;
typedef  void* u64 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int dccps_l_ack_ratio; } ;
struct ccid2_seq {void* ccid2s_seq; int ccid2s_acked; struct ccid2_seq* ccid2s_next; struct ccid2_seq* ccid2s_prev; } ;
struct ccid2_hc_tx_sock {int ccid2hctx_rpdupack; void* ccid2hctx_rpseq; void* ccid2hctx_high_ack; scalar_t__ ccid2hctx_cwnd; scalar_t__ ccid2hctx_ssthresh; struct ccid2_seq* ccid2hctx_seqt; struct ccid2_seq* ccid2hctx_seqh; } ;
struct TYPE_2__ {int dccpd_type; void* dccpd_ack_seq; void* dccpd_seq; } ;

/* Variables and functions */
 unsigned char DCCP_ACKVEC_LEN_MASK ; 
 scalar_t__ const DCCP_ACKVEC_STATE_ECN_MARKED ; 
 unsigned char DCCP_ACKVEC_STATE_MASK ; 
 scalar_t__ const DCCP_ACKVEC_STATE_NOT_RECEIVED ; 
#define  DCCP_PKT_ACK 129 
#define  DCCP_PKT_DATAACK 128 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 unsigned int DIV_ROUND_UP (int,int) ; 
 int NUMDUPACK ; 
 void* SUB48 (void*,scalar_t__ const) ; 
 scalar_t__ after48 (void*,void*) ; 
 scalar_t__ before48 (void*,void*) ; 
 scalar_t__ between48 (void*,void*,void*) ; 
 int ccid2_ackvector (struct sock*,struct sk_buff*,int,unsigned char**,unsigned char*) ; 
 int /*<<< orphan*/  ccid2_change_l_ack_ratio (struct sock*,int) ; 
 int /*<<< orphan*/  ccid2_congestion_event (struct sock*,struct ccid2_seq*) ; 
 int /*<<< orphan*/  ccid2_hc_tx_check_sanity (struct ccid2_hc_tx_sock*) ; 
 int /*<<< orphan*/  ccid2_hc_tx_dec_pipe (struct sock*) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid2_new_ack (struct sock*,struct ccid2_seq*,unsigned int*) ; 
 int /*<<< orphan*/  ccid2_pr_debug (char*,unsigned long long,...) ; 
 int dccp_delta_seqno (void*,void*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

__attribute__((used)) static void ccid2_hc_tx_packet_recv(struct sock *sk, struct sk_buff *skb)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);
	u64 ackno, seqno;
	struct ccid2_seq *seqp;
	unsigned char *vector;
	unsigned char veclen;
	int offset = 0;
	int done = 0;
	unsigned int maxincr = 0;

	ccid2_hc_tx_check_sanity(hctx);
	/* check reverse path congestion */
	seqno = DCCP_SKB_CB(skb)->dccpd_seq;

	/* XXX this whole "algorithm" is broken.  Need to fix it to keep track
	 * of the seqnos of the dupacks so that rpseq and rpdupack are correct
	 * -sorbo.
	 */
	/* need to bootstrap */
	if (hctx->ccid2hctx_rpdupack == -1) {
		hctx->ccid2hctx_rpdupack = 0;
		hctx->ccid2hctx_rpseq = seqno;
	} else {
		/* check if packet is consecutive */
		if (dccp_delta_seqno(hctx->ccid2hctx_rpseq, seqno) == 1)
			hctx->ccid2hctx_rpseq = seqno;
		/* it's a later packet */
		else if (after48(seqno, hctx->ccid2hctx_rpseq)) {
			hctx->ccid2hctx_rpdupack++;

			/* check if we got enough dupacks */
			if (hctx->ccid2hctx_rpdupack >= NUMDUPACK) {
				hctx->ccid2hctx_rpdupack = -1; /* XXX lame */
				hctx->ccid2hctx_rpseq = 0;

				ccid2_change_l_ack_ratio(sk, 2 * dp->dccps_l_ack_ratio);
			}
		}
	}

	/* check forward path congestion */
	/* still didn't send out new data packets */
	if (hctx->ccid2hctx_seqh == hctx->ccid2hctx_seqt)
		return;

	switch (DCCP_SKB_CB(skb)->dccpd_type) {
	case DCCP_PKT_ACK:
	case DCCP_PKT_DATAACK:
		break;
	default:
		return;
	}

	ackno = DCCP_SKB_CB(skb)->dccpd_ack_seq;
	if (after48(ackno, hctx->ccid2hctx_high_ack))
		hctx->ccid2hctx_high_ack = ackno;

	seqp = hctx->ccid2hctx_seqt;
	while (before48(seqp->ccid2s_seq, ackno)) {
		seqp = seqp->ccid2s_next;
		if (seqp == hctx->ccid2hctx_seqh) {
			seqp = hctx->ccid2hctx_seqh->ccid2s_prev;
			break;
		}
	}

	/*
	 * In slow-start, cwnd can increase up to a maximum of Ack Ratio/2
	 * packets per acknowledgement. Rounding up avoids that cwnd is not
	 * advanced when Ack Ratio is 1 and gives a slight edge otherwise.
	 */
	if (hctx->ccid2hctx_cwnd < hctx->ccid2hctx_ssthresh)
		maxincr = DIV_ROUND_UP(dp->dccps_l_ack_ratio, 2);

	/* go through all ack vectors */
	while ((offset = ccid2_ackvector(sk, skb, offset,
					 &vector, &veclen)) != -1) {
		/* go through this ack vector */
		while (veclen--) {
			const u8 rl = *vector & DCCP_ACKVEC_LEN_MASK;
			u64 ackno_end_rl = SUB48(ackno, rl);

			ccid2_pr_debug("ackvec start:%llu end:%llu\n",
				       (unsigned long long)ackno,
				       (unsigned long long)ackno_end_rl);
			/* if the seqno we are analyzing is larger than the
			 * current ackno, then move towards the tail of our
			 * seqnos.
			 */
			while (after48(seqp->ccid2s_seq, ackno)) {
				if (seqp == hctx->ccid2hctx_seqt) {
					done = 1;
					break;
				}
				seqp = seqp->ccid2s_prev;
			}
			if (done)
				break;

			/* check all seqnos in the range of the vector
			 * run length
			 */
			while (between48(seqp->ccid2s_seq,ackno_end_rl,ackno)) {
				const u8 state = *vector &
						 DCCP_ACKVEC_STATE_MASK;

				/* new packet received or marked */
				if (state != DCCP_ACKVEC_STATE_NOT_RECEIVED &&
				    !seqp->ccid2s_acked) {
					if (state ==
					    DCCP_ACKVEC_STATE_ECN_MARKED) {
						ccid2_congestion_event(sk,
								       seqp);
					} else
						ccid2_new_ack(sk, seqp,
							      &maxincr);

					seqp->ccid2s_acked = 1;
					ccid2_pr_debug("Got ack for %llu\n",
						       (unsigned long long)seqp->ccid2s_seq);
					ccid2_hc_tx_dec_pipe(sk);
				}
				if (seqp == hctx->ccid2hctx_seqt) {
					done = 1;
					break;
				}
				seqp = seqp->ccid2s_prev;
			}
			if (done)
				break;

			ackno = SUB48(ackno_end_rl, 1);
			vector++;
		}
		if (done)
			break;
	}

	/* The state about what is acked should be correct now
	 * Check for NUMDUPACK
	 */
	seqp = hctx->ccid2hctx_seqt;
	while (before48(seqp->ccid2s_seq, hctx->ccid2hctx_high_ack)) {
		seqp = seqp->ccid2s_next;
		if (seqp == hctx->ccid2hctx_seqh) {
			seqp = hctx->ccid2hctx_seqh->ccid2s_prev;
			break;
		}
	}
	done = 0;
	while (1) {
		if (seqp->ccid2s_acked) {
			done++;
			if (done == NUMDUPACK)
				break;
		}
		if (seqp == hctx->ccid2hctx_seqt)
			break;
		seqp = seqp->ccid2s_prev;
	}

	/* If there are at least 3 acknowledgements, anything unacknowledged
	 * below the last sequence number is considered lost
	 */
	if (done == NUMDUPACK) {
		struct ccid2_seq *last_acked = seqp;

		/* check for lost packets */
		while (1) {
			if (!seqp->ccid2s_acked) {
				ccid2_pr_debug("Packet lost: %llu\n",
					       (unsigned long long)seqp->ccid2s_seq);
				/* XXX need to traverse from tail -> head in
				 * order to detect multiple congestion events in
				 * one ack vector.
				 */
				ccid2_congestion_event(sk, seqp);
				ccid2_hc_tx_dec_pipe(sk);
			}
			if (seqp == hctx->ccid2hctx_seqt)
				break;
			seqp = seqp->ccid2s_prev;
		}

		hctx->ccid2hctx_seqt = last_acked;
	}

	/* trim acked packets in tail */
	while (hctx->ccid2hctx_seqt != hctx->ccid2hctx_seqh) {
		if (!hctx->ccid2hctx_seqt->ccid2s_acked)
			break;

		hctx->ccid2hctx_seqt = hctx->ccid2hctx_seqt->ccid2s_next;
	}

	ccid2_hc_tx_check_sanity(hctx);
}