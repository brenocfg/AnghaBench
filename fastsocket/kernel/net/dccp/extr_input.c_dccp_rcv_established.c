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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {int /*<<< orphan*/ * dccps_hc_rx_ackvec; } ;
struct dccp_hdr {int dummy; } ;
struct TYPE_2__ {scalar_t__ dccpd_ack_seq; int /*<<< orphan*/  dccpd_seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_ACKVEC_STATE_RECEIVED ; 
 scalar_t__ DCCP_PKT_WITHOUT_ACK_SEQ ; 
 TYPE_1__* DCCP_SKB_CB (struct sk_buff*) ; 
 int __dccp_rcv_established (struct sock*,struct sk_buff*,struct dccp_hdr const*,unsigned int const) ; 
 int /*<<< orphan*/  __kfree_skb (struct sk_buff*) ; 
 scalar_t__ dccp_ackvec_add (int /*<<< orphan*/ *,struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dccp_check_seqno (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_deliver_input_to_ccids (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_event_ack_recv (struct sock*,struct sk_buff*) ; 
 scalar_t__ dccp_parse_options (struct sock*,int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 

int dccp_rcv_established(struct sock *sk, struct sk_buff *skb,
			 const struct dccp_hdr *dh, const unsigned len)
{
	struct dccp_sock *dp = dccp_sk(sk);

	if (dccp_check_seqno(sk, skb))
		goto discard;

	if (dccp_parse_options(sk, NULL, skb))
		return 1;

	if (DCCP_SKB_CB(skb)->dccpd_ack_seq != DCCP_PKT_WITHOUT_ACK_SEQ)
		dccp_event_ack_recv(sk, skb);

	if (dp->dccps_hc_rx_ackvec != NULL &&
	    dccp_ackvec_add(dp->dccps_hc_rx_ackvec, sk,
			    DCCP_SKB_CB(skb)->dccpd_seq,
			    DCCP_ACKVEC_STATE_RECEIVED))
		goto discard;
	dccp_deliver_input_to_ccids(sk, skb);

	return __dccp_rcv_established(sk, skb, dh, len);
discard:
	__kfree_skb(skb);
	return 0;
}