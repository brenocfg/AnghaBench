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
struct gomp_work_share {size_t ordered_owner; } ;
struct TYPE_2__ {size_t team_id; struct gomp_work_share* work_share; struct gomp_team* team; } ;
struct gomp_thread {TYPE_1__ ts; } ;
struct gomp_team {int nthreads; int /*<<< orphan*/ * ordered_release; } ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_sem_wait (int /*<<< orphan*/ ) ; 
 struct gomp_thread* gomp_thread () ; 

void
gomp_ordered_sync (void)
{
  struct gomp_thread *thr = gomp_thread ();
  struct gomp_team *team = thr->ts.team;
  struct gomp_work_share *ws = thr->ts.work_share;

  /* Work share constructs can be orphaned.  But this clearly means that
     we are the only thread, and so we automatically own the section.  */
  if (team == NULL || team->nthreads == 1)
    return;

  /* ??? I believe it to be safe to access this data without taking the
     ws->lock.  The only presumed race condition is with the previous
     thread on the queue incrementing ordered_cur such that it points
     to us, concurrently with our check below.  But our team_id is
     already present in the queue, and the other thread will always
     post to our release semaphore.  So the two cases are that we will
     either win the race an momentarily block on the semaphore, or lose
     the race and find the semaphore already unlocked and so not block.
     Either way we get correct results.  */

  if (ws->ordered_owner != thr->ts.team_id)
    {
      gomp_sem_wait (team->ordered_release[thr->ts.team_id]);
      ws->ordered_owner = thr->ts.team_id;
    }
}