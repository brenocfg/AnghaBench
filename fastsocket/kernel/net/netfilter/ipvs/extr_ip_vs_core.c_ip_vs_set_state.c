#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ip_vs_protocol {int (* state_transition ) (struct ip_vs_conn*,int,struct sk_buff const*,struct ip_vs_protocol*) ;} ;
struct ip_vs_conn {int dummy; } ;

/* Variables and functions */
 int stub1 (struct ip_vs_conn*,int,struct sk_buff const*,struct ip_vs_protocol*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int
ip_vs_set_state(struct ip_vs_conn *cp, int direction,
		const struct sk_buff *skb,
		struct ip_vs_protocol *pp)
{
	if (unlikely(!pp->state_transition))
		return 0;
	return pp->state_transition(cp, direction, skb, pp);
}