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
struct TYPE_5__ {struct gomp_team* team; } ;
struct gomp_team {int nthreads; TYPE_2__ prev_ts; } ;
struct TYPE_4__ {struct gomp_team* team; } ;
struct TYPE_6__ {TYPE_1__ ts; } ;

/* Variables and functions */
 TYPE_3__* gomp_thread () ; 

int omp_in_parallel (void)
{
  struct gomp_team *team = gomp_thread ()->ts.team;

  while (team)
    {
      if (team->nthreads > 1)
	return true;
      team = team->prev_ts.team;
    }

  return false;
}