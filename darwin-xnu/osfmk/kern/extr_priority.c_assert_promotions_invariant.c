#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {scalar_t__ promotions; int sched_flags; } ;

/* Variables and functions */
 int TH_SFLAG_PROMOTED ; 
 int /*<<< orphan*/  assert (int) ; 

void
assert_promotions_invariant(thread_t thread)
{
	if (thread->promotions > 0)
		assert((thread->sched_flags & TH_SFLAG_PROMOTED) == TH_SFLAG_PROMOTED);

	if (thread->promotions == 0)
		assert((thread->sched_flags & TH_SFLAG_PROMOTED) != TH_SFLAG_PROMOTED);
}