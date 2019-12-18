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
struct TYPE_3__ {unsigned int total; scalar_t__ arrived; int /*<<< orphan*/  sem2; int /*<<< orphan*/  sem1; int /*<<< orphan*/  mutex2; int /*<<< orphan*/  mutex1; } ;
typedef  TYPE_1__ gomp_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
gomp_barrier_init (gomp_barrier_t *bar, unsigned count)
{
  gomp_mutex_init (&bar->mutex1);
#ifndef HAVE_SYNC_BUILTINS
  gomp_mutex_init (&bar->mutex2);
#endif
  gomp_sem_init (&bar->sem1, 0);
  gomp_sem_init (&bar->sem2, 0);
  bar->total = count;
  bar->arrived = 0;
}