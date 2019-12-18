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
struct TYPE_3__ {int depth; scalar_t__ owner; int /*<<< orphan*/  counter; } ;
typedef  TYPE_1__ __gthread_recursive_mutex_t ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetCurrentThreadId () ; 
 scalar_t__ __GTHR_W32_InterlockedCompareExchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
__gthr_win32_recursive_mutex_trylock (__gthread_recursive_mutex_t *mutex)
{
  DWORD me = GetCurrentThreadId();
  if (__GTHR_W32_InterlockedCompareExchange (&mutex->counter, 0, -1) < 0)
    {
      mutex->depth = 1;
      mutex->owner = me;
    }
  else if (mutex->owner == me)
    ++(mutex->depth);
  else
    return 1;

  return 0;
}