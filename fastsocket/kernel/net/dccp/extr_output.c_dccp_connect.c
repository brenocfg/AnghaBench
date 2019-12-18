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
struct sock {TYPE_1__* sk_prot; int /*<<< orphan*/  sk_allocation; } ;
struct sk_buff {int dummy; } ;
struct inet_connection_sock {int /*<<< orphan*/  icsk_rto; } ;
struct TYPE_4__ {int /*<<< orphan*/  dccpd_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCCP_INC_STATS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DCCP_MIB_ACTIVEOPENS ; 
 int /*<<< orphan*/  DCCP_PKT_REQUEST ; 
 int /*<<< orphan*/  DCCP_RTO_MAX ; 
 TYPE_2__* DCCP_SKB_CB (struct sk_buff*) ; 
 int ENOBUFS ; 
 int EPROTO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICSK_TIME_RETRANS ; 
 struct sk_buff* alloc_skb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_connect_init (struct sock*) ; 
 scalar_t__ dccp_feat_finalise_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dccp_sk (struct sock*) ; 
 int /*<<< orphan*/  dccp_skb_entail (struct sock*,struct sk_buff*) ; 
 int /*<<< orphan*/  dccp_transmit_skb (struct sock*,int /*<<< orphan*/ ) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  inet_csk_reset_xmit_timer (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int dccp_connect(struct sock *sk)
{
	struct sk_buff *skb;
	struct inet_connection_sock *icsk = inet_csk(sk);

	/* do not connect if feature negotiation setup fails */
	if (dccp_feat_finalise_settings(dccp_sk(sk)))
		return -EPROTO;

	dccp_connect_init(sk);

	skb = alloc_skb(sk->sk_prot->max_header, sk->sk_allocation);
	if (unlikely(skb == NULL))
		return -ENOBUFS;

	/* Reserve space for headers. */
	skb_reserve(skb, sk->sk_prot->max_header);

	DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_REQUEST;

	dccp_skb_entail(sk, skb);
	dccp_transmit_skb(sk, skb_clone(skb, GFP_KERNEL));
	DCCP_INC_STATS(DCCP_MIB_ACTIVEOPENS);

	/* Timer for repeating the REQUEST until an answer. */
	inet_csk_reset_xmit_timer(sk, ICSK_TIME_RETRANS,
				  icsk->icsk_rto, DCCP_RTO_MAX);
	return 0;
}