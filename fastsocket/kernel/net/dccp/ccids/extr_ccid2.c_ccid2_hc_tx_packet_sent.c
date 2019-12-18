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
struct sock {int dummy; } ;
struct dccp_sock {int dccps_l_ack_ratio; scalar_t__ dccps_gss; } ;
struct ccid2_seq {struct ccid2_seq* ccid2s_next; int /*<<< orphan*/  ccid2s_sent; scalar_t__ ccid2s_acked; scalar_t__ ccid2s_seq; } ;
struct ccid2_hc_tx_sock {int ccid2hctx_cwnd; int ccid2hctx_arsent; struct ccid2_seq* ccid2hctx_seqh; struct ccid2_seq* ccid2hctx_seqt; int /*<<< orphan*/  ccid2hctx_rtotimer; scalar_t__ ccid2hctx_ackloss; int /*<<< orphan*/  ccid2hctx_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DCCP_CRIT (char*) ; 
 int /*<<< orphan*/  ccid2_change_l_ack_ratio (struct sock*,int) ; 
 scalar_t__ ccid2_hc_tx_alloc_seq (struct ccid2_hc_tx_sock*) ; 
 int /*<<< orphan*/  ccid2_hc_tx_check_sanity (struct ccid2_hc_tx_sock*) ; 
 struct ccid2_hc_tx_sock* ccid2_hc_tx_sk (struct sock*) ; 
 int /*<<< orphan*/  ccid2_pr_debug (char*,...) ; 
 int /*<<< orphan*/  ccid2_start_rto_timer (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccid2_hc_tx_packet_sent(struct sock *sk, int more, unsigned int len)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct ccid2_hc_tx_sock *hctx = ccid2_hc_tx_sk(sk);
	struct ccid2_seq *next;

	hctx->ccid2hctx_pipe++;

	hctx->ccid2hctx_seqh->ccid2s_seq   = dp->dccps_gss;
	hctx->ccid2hctx_seqh->ccid2s_acked = 0;
	hctx->ccid2hctx_seqh->ccid2s_sent  = jiffies;

	next = hctx->ccid2hctx_seqh->ccid2s_next;
	/* check if we need to alloc more space */
	if (next == hctx->ccid2hctx_seqt) {
		if (ccid2_hc_tx_alloc_seq(hctx)) {
			DCCP_CRIT("packet history - out of memory!");
			/* FIXME: find a more graceful way to bail out */
			return;
		}
		next = hctx->ccid2hctx_seqh->ccid2s_next;
		BUG_ON(next == hctx->ccid2hctx_seqt);
	}
	hctx->ccid2hctx_seqh = next;

	ccid2_pr_debug("cwnd=%d pipe=%d\n", hctx->ccid2hctx_cwnd,
		       hctx->ccid2hctx_pipe);

	/*
	 * FIXME: The code below is broken and the variables have been removed
	 * from the socket struct. The `ackloss' variable was always set to 0,
	 * and with arsent there are several problems:
	 *  (i) it doesn't just count the number of Acks, but all sent packets;
	 *  (ii) it is expressed in # of packets, not # of windows, so the
	 *  comparison below uses the wrong formula: Appendix A of RFC 4341
	 *  comes up with the number K = cwnd / (R^2 - R) of consecutive windows
	 *  of data with no lost or marked Ack packets. If arsent were the # of
	 *  consecutive Acks received without loss, then Ack Ratio needs to be
	 *  decreased by 1 when
	 *	      arsent >=  K * cwnd / R  =  cwnd^2 / (R^3 - R^2)
	 *  where cwnd / R is the number of Acks received per window of data
	 *  (cf. RFC 4341, App. A). The problems are that
	 *  - arsent counts other packets as well;
	 *  - the comparison uses a formula different from RFC 4341;
	 *  - computing a cubic/quadratic equation each time is too complicated.
	 *  Hence a different algorithm is needed.
	 */
#if 0
	/* Ack Ratio.  Need to maintain a concept of how many windows we sent */
	hctx->ccid2hctx_arsent++;
	/* We had an ack loss in this window... */
	if (hctx->ccid2hctx_ackloss) {
		if (hctx->ccid2hctx_arsent >= hctx->ccid2hctx_cwnd) {
			hctx->ccid2hctx_arsent	= 0;
			hctx->ccid2hctx_ackloss	= 0;
		}
	} else {
		/* No acks lost up to now... */
		/* decrease ack ratio if enough packets were sent */
		if (dp->dccps_l_ack_ratio > 1) {
			/* XXX don't calculate denominator each time */
			int denom = dp->dccps_l_ack_ratio * dp->dccps_l_ack_ratio -
				    dp->dccps_l_ack_ratio;

			denom = hctx->ccid2hctx_cwnd * hctx->ccid2hctx_cwnd / denom;

			if (hctx->ccid2hctx_arsent >= denom) {
				ccid2_change_l_ack_ratio(sk, dp->dccps_l_ack_ratio - 1);
				hctx->ccid2hctx_arsent = 0;
			}
		} else {
			/* we can't increase ack ratio further [1] */
			hctx->ccid2hctx_arsent = 0; /* or maybe set it to cwnd*/
		}
	}
#endif

	/* setup RTO timer */
	if (!timer_pending(&hctx->ccid2hctx_rtotimer))
		ccid2_start_rto_timer(sk);

#ifdef CONFIG_IP_DCCP_CCID2_DEBUG
	do {
		struct ccid2_seq *seqp = hctx->ccid2hctx_seqt;

		while (seqp != hctx->ccid2hctx_seqh) {
			ccid2_pr_debug("out seq=%llu acked=%d time=%lu\n",
				       (unsigned long long)seqp->ccid2s_seq,
				       seqp->ccid2s_acked, seqp->ccid2s_sent);
			seqp = seqp->ccid2s_next;
		}
	} while (0);
	ccid2_pr_debug("=========\n");
	ccid2_hc_tx_check_sanity(hctx);
#endif
}