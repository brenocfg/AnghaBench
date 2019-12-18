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
struct TYPE_2__ {struct gomp_team* team; } ;
struct gomp_thread {TYPE_1__ ts; } ;
struct gomp_team {TYPE_1__ prev_ts; int /*<<< orphan*/  barrier; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_team (struct gomp_team*) ; 
 int /*<<< orphan*/  gomp_barrier_wait (int /*<<< orphan*/ *) ; 
 struct gomp_thread* gomp_thread () ; 

void
gomp_team_end (void)
{
  struct gomp_thread *thr = gomp_thread ();
  struct gomp_team *team = thr->ts.team;

  gomp_barrier_wait (&team->barrier);

  thr->ts = team->prev_ts;

  free_team (team);
}