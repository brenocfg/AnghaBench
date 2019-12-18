#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pthread_spinlock_t ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  interlock; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONGPTR ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONG ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 TYPE_2__* PTHREAD_SPINLOCK_INITIALIZER ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PTW32_SPIN_LOCKED 130 
#define  PTW32_SPIN_UNLOCKED 129 
#define  PTW32_SPIN_USE_MUTEX 128 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int
pthread_spin_unlock (pthread_spinlock_t * lock)
{
  register pthread_spinlock_t s;

  if (NULL == lock || NULL == *lock)
    {
      return (EINVAL);
    }

  s = *lock;

  if (s == PTHREAD_SPINLOCK_INITIALIZER)
    {
      return EPERM;
    }

  switch ((long)
	  PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG ((PTW32_INTERLOCKED_LONGPTR) &s->interlock,
					      (PTW32_INTERLOCKED_LONG) PTW32_SPIN_UNLOCKED,
					      (PTW32_INTERLOCKED_LONG) PTW32_SPIN_LOCKED))
    {
    case PTW32_SPIN_LOCKED:
    case PTW32_SPIN_UNLOCKED:
      return 0;
    case PTW32_SPIN_USE_MUTEX:
      return pthread_mutex_unlock (&(s->u.mutex));
    }

  return EINVAL;
}