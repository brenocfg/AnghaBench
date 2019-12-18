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
struct sched_entity {int dummy; } ;
struct cfs_rq {struct sched_entity* skip; struct sched_entity* next; struct sched_entity* last; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_buddies_last (struct sched_entity*) ; 
 int /*<<< orphan*/  __clear_buddies_next (struct sched_entity*) ; 
 int /*<<< orphan*/  __clear_buddies_skip (struct sched_entity*) ; 

__attribute__((used)) static void clear_buddies(struct cfs_rq *cfs_rq, struct sched_entity *se)
{
	if (cfs_rq->last == se)
		__clear_buddies_last(se);

	if (cfs_rq->next == se)
		__clear_buddies_next(se);

	if (cfs_rq->skip == se)
		__clear_buddies_skip(se);
}