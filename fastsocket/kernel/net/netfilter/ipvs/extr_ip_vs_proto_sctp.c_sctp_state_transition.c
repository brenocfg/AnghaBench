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
struct ip_vs_protocol {int dummy; } ;
struct ip_vs_conn {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int set_sctp_state (struct ip_vs_protocol*,struct ip_vs_conn*,int,struct sk_buff const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sctp_state_transition(struct ip_vs_conn *cp, int direction,
		const struct sk_buff *skb, struct ip_vs_protocol *pp)
{
	int ret = 0;

	spin_lock(&cp->lock);
	ret = set_sctp_state(pp, cp, direction, skb);
	spin_unlock(&cp->lock);

	return ret;
}