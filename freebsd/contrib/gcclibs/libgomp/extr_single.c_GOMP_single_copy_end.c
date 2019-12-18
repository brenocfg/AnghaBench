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
struct TYPE_4__ {TYPE_1__* work_share; struct gomp_team* team; } ;
struct gomp_thread {TYPE_2__ ts; } ;
struct gomp_team {int /*<<< orphan*/  barrier; } ;
struct TYPE_3__ {void* copyprivate; } ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_barrier_wait (int /*<<< orphan*/ *) ; 
 struct gomp_thread* gomp_thread () ; 
 int /*<<< orphan*/  gomp_work_share_end_nowait () ; 

void
GOMP_single_copy_end (void *data)
{
  struct gomp_thread *thr = gomp_thread ();
  struct gomp_team *team = thr->ts.team;

  if (team != NULL)
    {
      thr->ts.work_share->copyprivate = data;
      gomp_barrier_wait (&team->barrier);
    }

  gomp_work_share_end_nowait ();
}