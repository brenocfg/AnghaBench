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
struct gomp_work_share {int dummy; } ;
struct gomp_team {int generation_mask; unsigned int nthreads; int /*<<< orphan*/  master_release; int /*<<< orphan*/ ** ordered_release; int /*<<< orphan*/  barrier; struct gomp_work_share** work_shares; int /*<<< orphan*/  num_live_gen; int /*<<< orphan*/  oldest_live_gen; int /*<<< orphan*/  work_share_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_barrier_init (int /*<<< orphan*/ *,unsigned int) ; 
 void* gomp_malloc (int) ; 
 int /*<<< orphan*/  gomp_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gomp_team *
new_team (unsigned nthreads, struct gomp_work_share *work_share)
{
  struct gomp_team *team;
  size_t size;

  size = sizeof (*team) + nthreads * sizeof (team->ordered_release[0]);
  team = gomp_malloc (size);
  gomp_mutex_init (&team->work_share_lock);

  team->work_shares = gomp_malloc (4 * sizeof (struct gomp_work_share *));
  team->generation_mask = 3;
  team->oldest_live_gen = work_share == NULL;
  team->num_live_gen = work_share != NULL;
  team->work_shares[0] = work_share;

  team->nthreads = nthreads;
  gomp_barrier_init (&team->barrier, nthreads);

  gomp_sem_init (&team->master_release, 0);
  team->ordered_release[0] = &team->master_release;

  return team;
}