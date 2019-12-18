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
struct tcp_sock {int ecn_flags; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
#define  INET_ECN_CE 129 
 int INET_ECN_MASK ; 
#define  INET_ECN_NOT_ECT 128 
 int TCP_ECN_DEMAND_CWR ; 
 int TCP_ECN_OK ; 
 int TCP_ECN_SEEN ; 
 TYPE_1__* TCP_SKB_CB (struct sk_buff const*) ; 
 int /*<<< orphan*/  tcp_enter_quickack_mode (struct sock*) ; 

__attribute__((used)) static inline void TCP_ECN_check_ce(struct tcp_sock *tp, const struct sk_buff *skb)
{
	if (!(tp->ecn_flags & TCP_ECN_OK))
		return;

	switch (TCP_SKB_CB(skb)->flags & INET_ECN_MASK) {
	case INET_ECN_NOT_ECT:
		/* Funny extension: if ECT is not set on a segment,
		 * and we already seen ECT on a previous segment,
		 * it is probably a retransmit.
		 */
		if (tp->ecn_flags & TCP_ECN_SEEN)
			tcp_enter_quickack_mode((struct sock *)tp);
		break;
	case INET_ECN_CE:
		tp->ecn_flags |= TCP_ECN_DEMAND_CWR;
		/* fallinto */
	default:
		tp->ecn_flags |= TCP_ECN_SEEN;
	}
}