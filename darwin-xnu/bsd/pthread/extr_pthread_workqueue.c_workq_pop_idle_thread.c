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
struct workqueue {int /*<<< orphan*/  wq_thidlecount; int /*<<< orphan*/  wq_threads_scheduled; int /*<<< orphan*/  wq_thrunlist; int /*<<< orphan*/  wq_thnewlist; int /*<<< orphan*/  wq_thidlelist; } ;
struct uthread {int uu_workq_flags; } ;

/* Variables and functions */
 struct uthread* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct uthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct uthread*,int /*<<< orphan*/ ) ; 
 int UT_WORKQ_DYING ; 
 int UT_WORKQ_OVERCOMMIT ; 
 int UT_WORKQ_RUNNING ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uu_workq_entry ; 
 int /*<<< orphan*/  workq_death_policy_evaluate (struct workqueue*,int) ; 

__attribute__((used)) static struct uthread *
workq_pop_idle_thread(struct workqueue *wq)
{
	struct uthread *uth;

	if ((uth = TAILQ_FIRST(&wq->wq_thidlelist))) {
		TAILQ_REMOVE(&wq->wq_thidlelist, uth, uu_workq_entry);
	} else {
		uth = TAILQ_FIRST(&wq->wq_thnewlist);
		TAILQ_REMOVE(&wq->wq_thnewlist, uth, uu_workq_entry);
	}
	TAILQ_INSERT_TAIL(&wq->wq_thrunlist, uth, uu_workq_entry);

	assert((uth->uu_workq_flags & UT_WORKQ_RUNNING) == 0);
	uth->uu_workq_flags |= UT_WORKQ_RUNNING | UT_WORKQ_OVERCOMMIT;
	wq->wq_threads_scheduled++;
	wq->wq_thidlecount--;

	if (__improbable(uth->uu_workq_flags & UT_WORKQ_DYING)) {
		uth->uu_workq_flags ^= UT_WORKQ_DYING;
		workq_death_policy_evaluate(wq, 1);
	}
	return uth;
}