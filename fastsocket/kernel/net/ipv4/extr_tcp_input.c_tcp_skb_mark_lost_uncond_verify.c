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
struct tcp_sock {int /*<<< orphan*/  lost_out; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int sacked; } ;

/* Variables and functions */
 int TCPCB_LOST ; 
 int TCPCB_SACKED_ACKED ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ tcp_skb_pcount (struct sk_buff*) ; 
 int /*<<< orphan*/  tcp_verify_retransmit_hint (struct tcp_sock*,struct sk_buff*) ; 

__attribute__((used)) static void tcp_skb_mark_lost_uncond_verify(struct tcp_sock *tp,
					    struct sk_buff *skb)
{
	tcp_verify_retransmit_hint(tp, skb);

	if (!(TCP_SKB_CB(skb)->sacked & (TCPCB_LOST|TCPCB_SACKED_ACKED))) {
		tp->lost_out += tcp_skb_pcount(skb);
		TCP_SKB_CB(skb)->sacked |= TCPCB_LOST;
	}
}