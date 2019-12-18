#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pthread_spinlock_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {scalar_t__ interlock; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONGPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_LONG ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__* PTHREAD_SPINLOCK_INITIALIZER ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PTW32_SPIN_LOCKED ; 
 scalar_t__ PTW32_SPIN_UNLOCKED ; 
 scalar_t__ PTW32_SPIN_USE_MUTEX ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int ptw32_spinlock_check_need_init (TYPE_2__**) ; 

int
pthread_spin_lock (pthread_spinlock_t * lock)
{
  register pthread_spinlock_t s;

  if (NULL == lock || NULL == *lock)
    {
      return (EINVAL);
    }

  if (*lock == PTHREAD_SPINLOCK_INITIALIZER)
    {
      int result;

      if ((result = ptw32_spinlock_check_need_init (lock)) != 0)
	{
	  return (result);
	}
    }

  s = *lock;

  while ((PTW32_INTERLOCKED_LONG) PTW32_SPIN_LOCKED ==
	 PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG ((PTW32_INTERLOCKED_LONGPTR) &s->interlock,
					          (PTW32_INTERLOCKED_LONG) PTW32_SPIN_LOCKED,
					          (PTW32_INTERLOCKED_LONG) PTW32_SPIN_UNLOCKED))
    {
    }

  if (s->interlock == PTW32_SPIN_LOCKED)
    {
      return 0;
    }
  else if (s->interlock == PTW32_SPIN_USE_MUTEX)
    {
      return pthread_mutex_lock (&(s->u.mutex));
    }

  return EINVAL;
}