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
struct TYPE_3__ {TYPE_2__* work_share; } ;
struct gomp_thread {TYPE_1__ ts; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS_DYNAMIC ; 
 int gomp_iter_dynamic_next (long*,long*) ; 
 int gomp_iter_dynamic_next_locked (long*,long*) ; 
 int /*<<< orphan*/  gomp_loop_init (TYPE_2__*,long,long,long,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  gomp_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gomp_thread* gomp_thread () ; 
 scalar_t__ gomp_work_share_start (int) ; 

__attribute__((used)) static bool
gomp_loop_dynamic_start (long start, long end, long incr, long chunk_size,
			 long *istart, long *iend)
{
  struct gomp_thread *thr = gomp_thread ();
  bool ret;

  if (gomp_work_share_start (false))
    gomp_loop_init (thr->ts.work_share, start, end, incr,
		    GFS_DYNAMIC, chunk_size);

#ifdef HAVE_SYNC_BUILTINS
  gomp_mutex_unlock (&thr->ts.work_share->lock);
  ret = gomp_iter_dynamic_next (istart, iend);
#else
  ret = gomp_iter_dynamic_next_locked (istart, iend);
  gomp_mutex_unlock (&thr->ts.work_share->lock);
#endif

  return ret;
}