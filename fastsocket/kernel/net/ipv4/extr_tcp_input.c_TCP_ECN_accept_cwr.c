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
struct tcp_sock {int /*<<< orphan*/  ecn_flags; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ cwr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_ECN_DEMAND_CWR ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void TCP_ECN_accept_cwr(struct tcp_sock *tp, struct sk_buff *skb)
{
	if (tcp_hdr(skb)->cwr)
		tp->ecn_flags &= ~TCP_ECN_DEMAND_CWR;
}