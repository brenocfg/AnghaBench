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
struct TYPE_3__ {scalar_t__ depth; int /*<<< orphan*/  sema; int /*<<< orphan*/  counter; scalar_t__ owner; } ;
typedef  TYPE_1__ __gthread_recursive_mutex_t ;

/* Variables and functions */
 scalar_t__ InterlockedDecrement (int /*<<< orphan*/ *) ; 
 scalar_t__ ReleaseSemaphore (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int
__gthr_win32_recursive_mutex_unlock (__gthread_recursive_mutex_t *mutex)
{
  --(mutex->depth);
  if (mutex->depth == 0)
    {
      mutex->owner = 0;

      if (InterlockedDecrement (&mutex->counter) >= 0)
	return ReleaseSemaphore (mutex->sema, 1, NULL) ? 0 : 1;
    }

  return 0;
}