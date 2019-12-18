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
struct gomp_team {int /*<<< orphan*/  master_release; int /*<<< orphan*/  barrier; int /*<<< orphan*/  work_share_lock; struct gomp_team* work_shares; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct gomp_team*) ; 
 int /*<<< orphan*/  gomp_barrier_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_sem_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_team (struct gomp_team *team)
{
  free (team->work_shares);
  gomp_mutex_destroy (&team->work_share_lock);
  gomp_barrier_destroy (&team->barrier);
  gomp_sem_destroy (&team->master_release);
  free (team);
}