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
struct ip6q {struct ip6q* ip6q_next; struct ip6q* ip6q_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  ip6qlock ; 

void
frag6_insque(struct ip6q *new, struct ip6q *old)
{
	LCK_MTX_ASSERT(&ip6qlock, LCK_MTX_ASSERT_OWNED);

	new->ip6q_prev = old;
	new->ip6q_next = old->ip6q_next;
	old->ip6q_next->ip6q_prev= new;
	old->ip6q_next = new;
}