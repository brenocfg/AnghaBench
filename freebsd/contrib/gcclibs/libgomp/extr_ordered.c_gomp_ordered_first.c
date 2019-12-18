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
struct gomp_work_share {unsigned int ordered_cur; unsigned int ordered_num_used; size_t* ordered_team_ids; } ;
struct TYPE_2__ {size_t team_id; struct gomp_work_share* work_share; struct gomp_team* team; } ;
struct gomp_thread {TYPE_1__ ts; } ;
struct gomp_team {int nthreads; int /*<<< orphan*/ * ordered_release; } ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_sem_post (int /*<<< orphan*/ ) ; 
 struct gomp_thread* gomp_thread () ; 

void
gomp_ordered_first (void)
{
  struct gomp_thread *thr = gomp_thread ();
  struct gomp_team *team = thr->ts.team;
  struct gomp_work_share *ws = thr->ts.work_share;
  unsigned index;

  /* Work share constructs can be orphaned.  */
  if (team == NULL || team->nthreads == 1)
    return;

  index = ws->ordered_cur + ws->ordered_num_used;
  if (index >= team->nthreads)
    index -= team->nthreads;
  ws->ordered_team_ids[index] = thr->ts.team_id;

  /* If this is the first and only thread in the queue, then there is
     no one to release us when we get to our ordered section.  Post to
     our own release queue now so that we won't block later.  */
  if (ws->ordered_num_used++ == 0)
    gomp_sem_post (team->ordered_release[thr->ts.team_id]);
}