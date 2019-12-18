#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* work_share; TYPE_1__* team; } ;
struct gomp_thread {TYPE_2__ ts; } ;
struct TYPE_6__ {void* copyprivate; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  barrier; } ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gomp_thread* gomp_thread () ; 
 int /*<<< orphan*/  gomp_work_share_end_nowait () ; 
 int gomp_work_share_start (int) ; 

void *
GOMP_single_copy_start (void)
{
  struct gomp_thread *thr = gomp_thread ();

  bool first;
  void *ret;

  first = gomp_work_share_start (false);
  gomp_mutex_unlock (&thr->ts.work_share->lock);
  
  if (first)
    ret = NULL;
  else
    {
      gomp_barrier_wait (&thr->ts.team->barrier);

      ret = thr->ts.work_share->copyprivate;
      gomp_work_share_end_nowait ();
    }

  return ret;
}