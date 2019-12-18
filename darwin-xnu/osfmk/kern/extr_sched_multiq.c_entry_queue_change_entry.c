#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sched_entry_t ;
typedef  int /*<<< orphan*/ * queue_t ;
typedef  int integer_t ;
typedef  TYPE_2__* entry_queue_t ;
struct TYPE_8__ {int /*<<< orphan*/ * queues; } ;
struct TYPE_7__ {int sched_pri; int /*<<< orphan*/  entry_links; } ;

/* Variables and functions */
 int SCHED_TAILQ ; 
 int /*<<< orphan*/  entry_queue_check_entry (TYPE_2__*,TYPE_1__*,int) ; 
 scalar_t__ multiq_sanity_check ; 
 int /*<<< orphan*/  re_queue_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_queue_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
entry_queue_change_entry(
                          entry_queue_t rq,
                          sched_entry_t entry,
                          integer_t     options)
{
	int     sched_pri   = entry->sched_pri;
	queue_t queue       = &rq->queues[sched_pri];

#if defined(MULTIQ_SANITY_CHECK)
	if (multiq_sanity_check) {
		entry_queue_check_entry(rq, entry, sched_pri);
	}
#endif

	if (options & SCHED_TAILQ)
		re_queue_tail(queue, &entry->entry_links);
	else
		re_queue_head(queue, &entry->entry_links);
}