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
struct sock {TYPE_1__* sk_prot; } ;
struct sk_buff {int dummy; } ;
struct dccp_sock {scalar_t__ dccps_role; int /*<<< orphan*/  dccps_server_timewait; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_PKT_CLOSE ; 
 int /*<<< orphan*/  DCCP_PKT_CLOSEREQ ; 
 scalar_t__ DCCP_ROLE_SERVER ; 
 int /*<<< orphan*/  DCCP_RTO_MAX ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  DCCP_TIMEOUT_INIT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 struct dccp_sock* dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_skb_entail (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_transmit_skb (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_write_xmit (struct sock*,int) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

void dccp_send_close(struct sock *sk, const int active)
{
	struct dccp_sock *dp = dccp_sk(sk);
	struct sk_buff *skb;
	const gfp_t prio = active ? GFP_KERNEL : GFP_ATOMIC;

	skb = alloc_skb(sk->sk_prot->max_header, prio);
	if (skb == NULL)
		return;

	/* Reserve space for headers and prepare control bits. */
	skb_reserve(skb, sk->sk_prot->max_header);
	if (dp->dccps_role == DCCP_ROLE_SERVER && !dp->dccps_server_timewait)
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_CLOSEREQ;
	else
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_CLOSE;

	if (active) {
		dccp_write_xmit(sk, 1);
		dccp_skb_entail(sk, skb);
		dccp_transmit_skb(sk, skb_clone(skb, prio));
		/*
		 * Retransmission timer for active-close: RFC 4340, 8.3 requires
		 * to retransmit the Close/CloseReq until the CLOSING/CLOSEREQ
		 * state can be left. The initial timeout is 2 RTTs.
		 * Since RTT measurement is done by the CCIDs, there is no easy
		 * way to get an RTT sample. The fallback RTT from RFC 4340, 3.4
		 * is too low (200ms); we use a high value to avoid unnecessary
		 * retransmissions when the link RTT is > 0.2 seconds.
		 * FIXME: Let main module sample RTTs and use that instead.
		 */
		inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
					  DCCP_TIMEOUT_INIT, DCCP_RTO_MAX);
	} else
		dccp_transmit_skb(sk, skb);
}