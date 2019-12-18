#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sock {int /*<<< orphan*/  sk_err; scalar_t__ sk_write_pending; int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/ * sk_send_head; } ;
struct sk_buff {int dummy; } ;
struct TYPE_9__ {scalar_t__ rskq_defer_accept; } ;
struct TYPE_8__ {scalar_t__ pingpong; } ;
struct inet_connection_sock {TYPE_4__ icsk_accept_queue; TYPE_3__ icsk_ack; TYPE_2__* icsk_af_ops; int /*<<< orphan*/  icsk_pmtu_cookie; } ;
struct TYPE_6__ {long dccpor_timestamp_echo; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_featneg; int /*<<< orphan*/  dccps_isr; int /*<<< orphan*/  dccps_swl; TYPE_1__ dccps_options_received; int /*<<< orphan*/  dccps_syn_rtt; scalar_t__ dccps_awh; scalar_t__ dccps_awl; } ;
struct dccp_hdr {scalar_t__ dccph_type; } ;
struct TYPE_10__ {int /*<<< orphan*/  dccpd_reset_code; int /*<<< orphan*/  dccpd_seq; scalar_t__ dccpd_ack_seq; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* rebuild_header ) (struct sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_CLOSED ; 
 int /*<<< orphan*/  DCCP_PARTOPEN ; 
 scalar_t__ DCCP_PKT_RESPONSE ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_ABORTED ; 
 int /*<<< orphan*/  DCCP_RESET_CODE_PACKET_ERROR ; 
 TYPE_5__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ECOMM ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 int /*<<< orphan*/  POLL_OUT ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  SOCK_WAKE_IO ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  between48 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ dccp_feat_activate_values (struct sock*,int /*<<< orphan*/ *) ; 
 scalar_t__ dccp_parse_options (struct sock*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,unsigned long long,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  dccp_sample_rtt (struct sock*,int) ; 
 int /*<<< orphan*/  dccp_send_ack (struct sock*) ; 
 int /*<<< orphan*/  dccp_set_seqno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_sync_mss (struct sock*,int /*<<< orphan*/ ) ; 
 long dccp_timestamp () ; 
 int /*<<< orphan*/  dccp_update_gsr (struct sock*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_clear_xmit_timer (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (long) ; 
 int /*<<< orphan*/  max48 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_wake_async (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  stub2 (struct sock*) ; 

__attribute__((used)) static int dccp_rcv_request_sent_state_process(struct sock *sk,
					       struct sk_buff *skb,
					       const struct dccp_hdr *dh,
					       const unsigned len)
{
	/*
	 *  Step 4: Prepare sequence numbers in REQUEST
	 *     If S.state == REQUEST,
	 *	  If (P.type == Response or P.type == Reset)
	 *		and S.AWL <= P.ackno <= S.AWH,
	 *	     / * Set sequence number variables corresponding to the
	 *		other endpoint, so P will pass the tests in Step 6 * /
	 *	     Set S.GSR, S.ISR, S.SWL, S.SWH
	 *	     / * Response processing continues in Step 10; Reset
	 *		processing continues in Step 9 * /
	*/
	if (dh->dccph_type == DCCP_PKT_RESPONSE) {
		const struct inet_connection_sock *icsk = inet_csk(sk);
		struct dccp_sock *dp = dccp_sk(sk);
		long tstamp = dccp_timestamp();

		if (!between48(DCCP_SKB_CB(skb)->dccpd_ack_seq,
			       dp->dccps_awl, dp->dccps_awh)) {
			dccp_pr_debug("invalid ackno: S.AWL=%llu, "
				      "P.ackno=%llu, S.AWH=%llu \n",
				      (unsigned long long)dp->dccps_awl,
			   (unsigned long long)DCCP_SKB_CB(skb)->dccpd_ack_seq,
				      (unsigned long long)dp->dccps_awh);
			goto out_invalid_packet;
		}

		/*
		 * If option processing (Step 8) failed, return 1 here so that
		 * dccp_v4_do_rcv() sends a Reset. The Reset code depends on
		 * the option type and is set in dccp_parse_options().
		 */
		if (dccp_parse_options(sk, NULL, skb))
			return 1;

		/* Obtain usec RTT sample from SYN exchange (used by CCID 3) */
		if (likely(dp->dccps_options_received.dccpor_timestamp_echo))
			dp->dccps_syn_rtt = dccp_sample_rtt(sk, 10 * (tstamp -
			    dp->dccps_options_received.dccpor_timestamp_echo));

		/* Stop the REQUEST timer */
		inet_csk_clear_xmit_timer(sk, ICSK_TIME_RETRANS);
		WARN_ON(sk->sk_send_head == NULL);
		kfree_skb(sk->sk_send_head);
		sk->sk_send_head = NULL;

		dp->dccps_isr = DCCP_SKB_CB(skb)->dccpd_seq;
		dccp_update_gsr(sk, dp->dccps_isr);
		/*
		 * SWL and AWL are initially adjusted so that they are not less than
		 * the initial Sequence Numbers received and sent, respectively:
		 *	SWL := max(GSR + 1 - floor(W/4), ISR),
		 *	AWL := max(GSS - W' + 1, ISS).
		 * These adjustments MUST be applied only at the beginning of the
		 * connection.
		 *
		 * AWL was adjusted in dccp_v4_connect -acme
		 */
		dccp_set_seqno(&dp->dccps_swl,
			       max48(dp->dccps_swl, dp->dccps_isr));

		dccp_sync_mss(sk, icsk->icsk_pmtu_cookie);

		/*
		 *    Step 10: Process REQUEST state (second part)
		 *       If S.state == REQUEST,
		 *	  / * If we get here, P is a valid Response from the
		 *	      server (see Step 4), and we should move to
		 *	      PARTOPEN state. PARTOPEN means send an Ack,
		 *	      don't send Data packets, retransmit Acks
		 *	      periodically, and always include any Init Cookie
		 *	      from the Response * /
		 *	  S.state := PARTOPEN
		 *	  Set PARTOPEN timer
		 *	  Continue with S.state == PARTOPEN
		 *	  / * Step 12 will send the Ack completing the
		 *	      three-way handshake * /
		 */
		dccp_set_state(sk, DCCP_PARTOPEN);

		/*
		 * If feature negotiation was successful, activate features now;
		 * an activation failure means that this host could not activate
		 * one ore more features (e.g. insufficient memory), which would
		 * leave at least one feature in an undefined state.
		 */
		if (dccp_feat_activate_values(sk, &dp->dccps_featneg))
			goto unable_to_proceed;

		/* Make sure socket is routed, for correct metrics. */
		icsk->icsk_af_ops->rebuild_header(sk);

		if (!sock_flag(sk, SOCK_DEAD)) {
			sk->sk_state_change(sk);
			sk_wake_async(sk, SOCK_WAKE_IO, POLL_OUT);
		}

		if (sk->sk_write_pending || icsk->icsk_ack.pingpong ||
		    icsk->icsk_accept_queue.rskq_defer_accept) {
			/* Save one ACK. Data will be ready after
			 * several ticks, if write_pending is set.
			 *
			 * It may be deleted, but with this feature tcpdumps
			 * look so _wonderfully_ clever, that I was not able
			 * to stand against the temptation 8)     --ANK
			 */
			/*
			 * OK, in DCCP we can as well do a similar trick, its
			 * even in the draft, but there is no need for us to
			 * schedule an ack here, as dccp_sendmsg does this for
			 * us, also stated in the draft. -acme
			 */
			__kfree_skb(skb);
			return 0;
		}
		dccp_send_ack(sk);
		return -1;
	}

out_invalid_packet:
	/* dccp_v4_do_rcv will send a reset */
	DCCP_SKB_CB(skb)->dccpd_reset_code = DCCP_RESET_CODE_PACKET_ERROR;
	return 1;

unable_to_proceed:
	DCCP_SKB_CB(skb)->dccpd_reset_code = DCCP_RESET_CODE_ABORTED;
	/*
	 * We mark this socket as no longer usable, so that the loop in
	 * dccp_sendmsg() terminates and the application gets notified.
	 */
	dccp_set_state(sk, DCCP_CLOSED);
	sk->sk_err = ECOMM;
	return 1;
}