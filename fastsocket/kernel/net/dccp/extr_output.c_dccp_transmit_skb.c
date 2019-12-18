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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct inet_sock {int /*<<< orphan*/  dport; int /*<<< orphan*/  sport; } ;
struct inet_connection_sock {TYPE_1__* icsk_af_ops; int /*<<< orphan*/  icsk_retransmits; } ;
struct dccp_sock {int /*<<< orphan*/  dccps_iss; int /*<<< orphan*/  dccps_awl; int /*<<< orphan*/  dccps_service; int /*<<< orphan*/  dccps_gss; int /*<<< orphan*/  dccps_pcslen; int /*<<< orphan*/  dccps_gsr; } ;
struct dccp_skb_cb {int dccpd_type; int const dccpd_opt_len; int /*<<< orphan*/  dccpd_reset_code; int /*<<< orphan*/  dccpd_seq; int /*<<< orphan*/  dccpd_ccval; int /*<<< orphan*/  dccpd_ack_seq; } ;
struct dccp_hdr_ext {int dummy; } ;
struct dccp_hdr {int dccph_type; int dccph_doff; int dccph_x; int /*<<< orphan*/  dccph_cscov; int /*<<< orphan*/  dccph_ccval; int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; } ;
struct TYPE_6__ {int /*<<< orphan*/  dccph_req_service; } ;
struct TYPE_5__ {int /*<<< orphan*/  dccph_reset_code; } ;
struct TYPE_4__ {int (* queue_xmit ) (struct sk_buff*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* send_check ) (struct sock*,int /*<<< orphan*/ ,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADD48 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DCCP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_OUTSEGS ; 
#define  DCCP_PKT_DATA 133 
#define  DCCP_PKT_DATAACK 132 
#define  DCCP_PKT_REQUEST 131 
#define  DCCP_PKT_RESET 130 
#define  DCCP_PKT_SYNC 129 
#define  DCCP_PKT_SYNCACK 128 
 struct dccp_skb_cb* DCCP_SKB_CB (struct sk_buff*) ; 
 int ENOBUFS ; 
 int EPROTO ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_event_ack_sent (struct sock*) ; 
 int /*<<< orphan*/  dccp_hdr_ack_bits (struct sk_buff*) ; 
 TYPE_3__* dccp_hdr_request (struct sk_buff*) ; 
 TYPE_2__* dccp_hdr_reset (struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_hdr_set_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_hdr_set_seq (struct dccp_hdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_insert_options (struct sock*,struct sk_buff*) ; 
 int dccp_packet_hdr_len (int) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_update_gss (struct sock*,int /*<<< orphan*/ ) ; 
 struct dccp_hdr* dccp_zeroed_hdr (struct sk_buff*,int const) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int net_xmit_eval (int) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,struct sock*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int stub2 (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_transmit_skb(struct sock *sk, struct sk_buff *skb)
{
	if (likely(skb != NULL)) {
		const struct inet_sock *inet = inet_sk(sk);
		const struct inet_connection_sock *icsk = inet_csk(sk);
		struct dccp_sock *dp = dccp_sk(sk);
		struct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
		struct dccp_hdr *dh;
		/* XXX For now we're using only 48 bits sequence numbers */
		const u32 dccp_header_size = sizeof(*dh) +
					     sizeof(struct dccp_hdr_ext) +
					  dccp_packet_hdr_len(dcb->dccpd_type);
		int err, set_ack = 1;
		u64 ackno = dp->dccps_gsr;
		/*
		 * Increment GSS here already in case the option code needs it.
		 * Update GSS for real only if option processing below succeeds.
		 */
		dcb->dccpd_seq = ADD48(dp->dccps_gss, 1);

		switch (dcb->dccpd_type) {
		case DCCP_PKT_DATA:
			set_ack = 0;
			/* fall through */
		case DCCP_PKT_DATAACK:
		case DCCP_PKT_RESET:
			break;

		case DCCP_PKT_REQUEST:
			set_ack = 0;
			/* Use ISS on the first (non-retransmitted) Request. */
			if (icsk->icsk_retransmits == 0)
				dcb->dccpd_seq = dp->dccps_iss;
			/* fall through */

		case DCCP_PKT_SYNC:
		case DCCP_PKT_SYNCACK:
			ackno = dcb->dccpd_ack_seq;
			/* fall through */
		default:
			/*
			 * Set owner/destructor: some skbs are allocated via
			 * alloc_skb (e.g. when retransmission may happen).
			 * Only Data, DataAck, and Reset packets should come
			 * through here with skb->sk set.
			 */
			WARN_ON(skb->sk);
			skb_set_owner_w(skb, sk);
			break;
		}

		if (dccp_insert_options(sk, skb)) {
			kfree_skb(skb);
			return -EPROTO;
		}


		/* Build DCCP header and checksum it. */
		dh = dccp_zeroed_hdr(skb, dccp_header_size);
		dh->dccph_type	= dcb->dccpd_type;
		dh->dccph_sport	= inet->sport;
		dh->dccph_dport	= inet->dport;
		dh->dccph_doff	= (dccp_header_size + dcb->dccpd_opt_len) / 4;
		dh->dccph_ccval	= dcb->dccpd_ccval;
		dh->dccph_cscov = dp->dccps_pcslen;
		/* XXX For now we're using only 48 bits sequence numbers */
		dh->dccph_x	= 1;

		dccp_update_gss(sk, dcb->dccpd_seq);
		dccp_hdr_set_seq(dh, dp->dccps_gss);
		if (set_ack)
			dccp_hdr_set_ack(dccp_hdr_ack_bits(skb), ackno);

		switch (dcb->dccpd_type) {
		case DCCP_PKT_REQUEST:
			dccp_hdr_request(skb)->dccph_req_service =
							dp->dccps_service;
			/*
			 * Limit Ack window to ISS <= P.ackno <= GSS, so that
			 * only Responses to Requests we sent are considered.
			 */
			dp->dccps_awl = dp->dccps_iss;
			break;
		case DCCP_PKT_RESET:
			dccp_hdr_reset(skb)->dccph_reset_code =
							dcb->dccpd_reset_code;
			break;
		}

		icsk->icsk_af_ops->send_check(sk, 0, skb);

		if (set_ack)
			dccp_event_ack_sent(sk);

		DCCP_INC_STATS(DCCP_MIB_OUTSEGS);

		err = icsk->icsk_af_ops->queue_xmit(skb, 0);
		return net_xmit_eval(err);
	}
	return -ENOBUFS;
}