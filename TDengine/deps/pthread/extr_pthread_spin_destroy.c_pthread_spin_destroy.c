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
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
typedef  TYPE_2__* pthread_spinlock_t ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {scalar_t__ interlock; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONGPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_LONG ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 TYPE_2__* PTHREAD_SPINLOCK_INITIALIZER ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PTW32_SPIN_INVALID ; 
 scalar_t__ PTW32_SPIN_UNLOCKED ; 
 scalar_t__ PTW32_SPIN_USE_MUTEX ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_spinlock_test_init_lock ; 

int
pthread_spin_destroy (pthread_spinlock_t * lock)
{
  register pthread_spinlock_t s;
  int result = 0;

  if (lock == NULL || *lock == NULL)
    {
      return EINVAL;
    }

  if ((s = *lock) != PTHREAD_SPINLOCK_INITIALIZER)
    {
      if (s->interlock == PTW32_SPIN_USE_MUTEX)
	{
	  result = pthread_mutex_destroy (&(s->u.mutex));
	}
      else if ((PTW32_INTERLOCKED_LONG) PTW32_SPIN_UNLOCKED !=
	       PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG ((PTW32_INTERLOCKED_LONGPTR) &s->interlock,
						   (PTW32_INTERLOCKED_LONG) PTW32_SPIN_INVALID,
						   (PTW32_INTERLOCKED_LONG) PTW32_SPIN_UNLOCKED))
	{
	  result = EINVAL;
	}

      if (0 == result)
	{
	  /*
	   * We are relying on the application to ensure that all other threads
	   * have finished with the spinlock before destroying it.
	   */
	  *lock = NULL;
	  (void) free (s);
	}
    }
  else
    {
      /*
       * See notes in ptw32_spinlock_check_need_init() above also.
       */
      ptw32_mcs_local_node_t node;

      ptw32_mcs_lock_acquire(&ptw32_spinlock_test_init_lock, &node);

      /*
       * Check again.
       */
      if (*lock == PTHREAD_SPINLOCK_INITIALIZER)
	{
	  /*
	   * This is all we need to do to destroy a statically
	   * initialised spinlock that has not yet been used (initialised).
	   * If we get to here, another thread
	   * waiting to initialise this mutex will get an EINVAL.
	   */
	  *lock = NULL;
	}
      else
	{
	  /*
	   * The spinlock has been initialised while we were waiting
	   * so assume it's in use.
	   */
	  result = EBUSY;
	}

       ptw32_mcs_lock_release(&node);
    }

  return (result);
}