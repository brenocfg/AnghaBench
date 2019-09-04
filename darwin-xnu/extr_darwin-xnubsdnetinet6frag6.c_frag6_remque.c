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
struct ip6q {TYPE_2__* ip6q_prev; TYPE_1__* ip6q_next; } ;
struct TYPE_4__ {TYPE_1__* ip6q_next; } ;
struct TYPE_3__ {TYPE_2__* ip6q_prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int /*<<< orphan*/  ip6qlock ; 

void
frag6_remque(struct ip6q *p6)
{
	LCK_MTX_ASSERT(&ip6qlock, LCK_MTX_ASSERT_OWNED);

	p6->ip6q_prev->ip6q_next = p6->ip6q_next;
	p6->ip6q_next->ip6q_prev = p6->ip6q_prev;
}