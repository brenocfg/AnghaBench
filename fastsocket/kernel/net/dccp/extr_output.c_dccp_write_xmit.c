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
typedef  int u32 ;
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_write_queue; } ;
struct sk_buff {int len; } ;
struct dccp_sock {int dccps_mss_cache; int /*<<< orphan*/  dccps_hc_tx_ccid; int /*<<< orphan*/  dccps_featneg; int /*<<< orphan*/  dccps_xmit_timer; } ;
struct dccp_skb_cb {void* dccpd_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  icsk_rto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_BUG (char*,int) ; 
 int DCCP_FEATNEG_OVERHEAD ; 
 scalar_t__ DCCP_PARTOPEN ; 
 void* DCCP_PKT_DATA ; 
 void* DCCP_PKT_DATAACK ; 
 int /*<<< orphan*/  DCCP_RTO_MAX ; 
 struct dccp_skb_cb* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DCCP_WARN (char*,int const) ; 
 int EINTR ; 
 int /*<<< orphan*/  ICSK_TIME_DACK ; 
 int /*<<< orphan*/  ccid_hc_tx_packet_sent (int /*<<< orphan*/ ,struct sock*,int /*<<< orphan*/ ,int const) ; 
 int ccid_hc_tx_send_packet (int /*<<< orphan*/ ,struct sock*,struct sk_buff*) ; 
 scalar_t__ dccp_ack_pending (struct sock*) ; 
 int /*<<< orphan*/  dccp_feat_list_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dccp_pr_debug (char*,int) ; 
 int /*<<< orphan*/  dccp_send_ack (struct sock*) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int dccp_transmit_skb (struct sock*,struct sk_buff*) ; 
 int dccp_wait_for_ccid (struct sock*,struct sk_buff*,int) ; 
 TYPE_1__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_csk_schedule_ack (struct sock*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  sk_reset_timer (struct sock*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_peek (int /*<<< orphan*/ *) ; 

void dccp_write_xmit(struct sock *sk, int block)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct sk_buff *skb;

	while ((skb = skb_peek(&sk->sk_write_queue))) {
		int err = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);

		if (err > 0) {
			if (!block) {
				sk_reset_timer(sk, &dp->dccps_xmit_timer,
						msecs_to_jiffies(err)+jiffies);
				break;
			} else
				err = dccp_wait_for_ccid(sk, skb, err);
			if (err && err != -EINTR)
				DCCP_BUG("err=%d after dccp_wait_for_ccid", err);
		}

		skb_dequeue(&sk->sk_write_queue);
		if (err == 0) {
			struct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
			const int len = skb->len;

			if (sk->sk_state == DCCP_PARTOPEN) {
				const u32 cur_mps = dp->dccps_mss_cache - DCCP_FEATNEG_OVERHEAD;
				/*
				 * See 8.1.5 - Handshake Completion.
				 *
				 * For robustness we resend Confirm options until the client has
				 * entered OPEN. During the initial feature negotiation, the MPS
				 * is smaller than usual, reduced by the Change/Confirm options.
				 */
				if (!list_empty(&dp->dccps_featneg) && len > cur_mps) {
					DCCP_WARN("Payload too large (%d) for featneg.\n", len);
					dccp_send_ack(sk);
					dccp_feat_list_purge(&dp->dccps_featneg);
				}

				inet_csk_schedule_ack(sk);
				inet_csk_reset_xmit_timer(sk, ICSK_TIME_DACK,
						  inet_csk(sk)->icsk_rto,
						  DCCP_RTO_MAX);
				dcb->dccpd_type = DCCP_PKT_DATAACK;
			} else if (dccp_ack_pending(sk))
				dcb->dccpd_type = DCCP_PKT_DATAACK;
			else
				dcb->dccpd_type = DCCP_PKT_DATA;

			err = dccp_transmit_skb(sk, skb);
			ccid_hc_tx_packet_sent(dp->dccps_hc_tx_ccid, sk, 0, len);
			if (err)
				DCCP_BUG("err=%d after ccid_hc_tx_packet_sent",
					 err);
		} else {
			dccp_pr_debug("packet discarded due to err=%d\n", err);
			kfree_skb(skb);
		}
	}
}