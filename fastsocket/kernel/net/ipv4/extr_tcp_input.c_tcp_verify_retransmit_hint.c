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
struct tcp_sock {int /*<<< orphan*/  retransmit_high; int /*<<< orphan*/  lost_out; struct sk_buff* retransmit_skb_hint; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  end_seq; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 TYPE_1__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tcp_verify_retransmit_hint(struct tcp_sock *tp, struct sk_buff *skb)
{
	if ((tp->retransmit_skb_hint == NULL) ||
	    before(TCP_SKB_CB(skb)->seq,
		   TCP_SKB_CB(tp->retransmit_skb_hint)->seq))
		tp->retransmit_skb_hint = skb;

	if (!tp->lost_out ||
	    after(TCP_SKB_CB(skb)->end_seq, tp->retransmit_high))
		tp->retransmit_high = TCP_SKB_CB(skb)->end_seq;
}