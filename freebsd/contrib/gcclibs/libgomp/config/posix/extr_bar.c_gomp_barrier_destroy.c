#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sem2; int /*<<< orphan*/  sem1; int /*<<< orphan*/  mutex2; int /*<<< orphan*/  mutex1; } ;
typedef  TYPE_1__ gomp_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_sem_destroy (int /*<<< orphan*/ *) ; 

void
gomp_barrier_destroy (gomp_barrier_t *bar)
{
  /* Before destroying, make sure all threads have left the barrier.  */
  gomp_mutex_lock (&bar->mutex1);
  gomp_mutex_unlock (&bar->mutex1);

  gomp_mutex_destroy (&bar->mutex1);
#ifndef HAVE_SYNC_BUILTINS
  gomp_mutex_destroy (&bar->mutex2);
#endif
  gomp_sem_destroy (&bar->sem1);
  gomp_sem_destroy (&bar->sem2);
}