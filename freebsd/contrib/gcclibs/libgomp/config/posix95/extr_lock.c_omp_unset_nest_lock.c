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
typedef  scalar_t__ pthread_t ;
struct TYPE_3__ {scalar_t__ count; int /*<<< orphan*/  lock; scalar_t__ owner; } ;
typedef  TYPE_1__ omp_nest_lock_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void
omp_unset_nest_lock (omp_nest_lock_t *lock)
{
  lock->count--;

  if (lock->count == 0)
    {
      lock->owner = (pthread_t) 0;
      pthread_mutex_unlock (&lock->lock);
    }
}