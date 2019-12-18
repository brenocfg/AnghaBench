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
struct sock {int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int dummy; } ;
struct dccp_hdr {int dccph_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_seq; } ;
struct TYPE_3__ {int /*<<< orphan*/  dccps_osr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_OPEN ; 
 int /*<<< orphan*/  DCCP_PARTOPEN ; 
#define  DCCP_PKT_ACK 131 
#define  DCCP_PKT_DATA 130 
#define  DCCP_PKT_DATAACK 129 
#define  DCCP_PKT_RESET 128 
 int /*<<< orphan*/  DCCP_RESPOND ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ICSK_TIME_DACK ; 
 int /*<<< orphan*/  __dccp_rcv_established (struct sock*,struct sk_buff*,struct dccp_hdr const*,unsigned int const) ; 
 int /*<<< orphan*/  dccp_set_state (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_clear_xmit_timer (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccp_rcv_respond_partopen_state_process(struct sock *sk,
						   struct sk_buff *skb,
						   const struct dccp_hdr *dh,
						   const unsigned len)
{
	int queued = 0;

	switch (dh->dccph_type) {
	case DCCP_PKT_RESET:
		inet_csk_clear_xmit_timer(sk, ICSK_TIME_DACK);
		break;
	case DCCP_PKT_DATA:
		if (sk->sk_state == DCCP_RESPOND)
			break;
	case DCCP_PKT_DATAACK:
	case DCCP_PKT_ACK:
		/*
		 * FIXME: we should be reseting the PARTOPEN (DELACK) timer
		 * here but only if we haven't used the DELACK timer for
		 * something else, like sending a delayed ack for a TIMESTAMP
		 * echo, etc, for now were not clearing it, sending an extra
		 * ACK when there is nothing else to do in DELACK is not a big
		 * deal after all.
		 */

		/* Stop the PARTOPEN timer */
		if (sk->sk_state == DCCP_PARTOPEN)
			inet_csk_clear_xmit_timer(sk, ICSK_TIME_DACK);

		dccp_sk(sk)->dccps_osr = DCCP_SKB_CB(skb)->dccpd_seq;
		dccp_set_state(sk, DCCP_OPEN);

		if (dh->dccph_type == DCCP_PKT_DATAACK ||
		    dh->dccph_type == DCCP_PKT_DATA) {
			__dccp_rcv_established(sk, skb, dh, len);
			queued = 1; /* packet was queued
				       (by __dccp_rcv_established) */
		}
		break;
	}

	return queued;
}