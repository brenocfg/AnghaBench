#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptw32_robust_state_t ;
typedef  void* pthread_t ;
typedef  TYPE_2__* pthread_mutex_t ;
struct TYPE_9__ {int kind; int recursive_count; int /*<<< orphan*/  event; int /*<<< orphan*/  lock_idx; void* ownerThread; TYPE_1__* robustNode; } ;
struct TYPE_8__ {int /*<<< orphan*/  stateInconsistent; } ;
typedef  int /*<<< orphan*/  PTW32_INTERLOCKED_LONGPTR ;
typedef  scalar_t__ PTW32_INTERLOCKED_LONG ;

/* Variables and functions */
 int EDEADLK ; 
 int EINVAL ; 
 int ENOTRECOVERABLE ; 
 int EOWNERDEAD ; 
 int /*<<< orphan*/  INFINITE ; 
 TYPE_2__* PTHREAD_ERRORCHECK_MUTEX_INITIALIZER ; 
 int PTHREAD_MUTEX_NORMAL ; 
 int PTHREAD_MUTEX_RECURSIVE ; 
 scalar_t__ PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ PTW32_INTERLOCKED_EXCHANGE_ADD_LONG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PTW32_INTERLOCKED_EXCHANGE_LONG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ PTW32_ROBUST_NOTRECOVERABLE ; 
 int /*<<< orphan*/  SetEvent (int /*<<< orphan*/ ) ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_equal (void*,void*) ; 
 void* pthread_self () ; 
 int ptw32_mutex_check_need_init (TYPE_2__**) ; 
 int /*<<< orphan*/  ptw32_robust_mutex_add (TYPE_2__**,void*) ; 
 int ptw32_robust_mutex_inherit (TYPE_2__**) ; 

int
pthread_mutex_lock (pthread_mutex_t * mutex)
{
  int kind;
  pthread_mutex_t mx;
  int result = 0;

  /*
   * Let the system deal with invalid pointers.
   */
  if (*mutex == NULL)
    {
      return EINVAL;
    }

  /*
   * We do a quick check to see if we need to do more work
   * to initialise a static mutex. We check
   * again inside the guarded section of ptw32_mutex_check_need_init()
   * to avoid race conditions.
   */
  if (*mutex >= PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
    {
      if ((result = ptw32_mutex_check_need_init (mutex)) != 0)
	{
	  return (result);
	}
    }

  mx = *mutex;
  kind = mx->kind;

  if (kind >= 0)
    {
      /* Non-robust */
      if (PTHREAD_MUTEX_NORMAL == kind)
        {
          if ((PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_EXCHANGE_LONG(
		       (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
		       (PTW32_INTERLOCKED_LONG) 1) != 0)
	    {
	      while ((PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_EXCHANGE_LONG(
                              (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
			      (PTW32_INTERLOCKED_LONG) -1) != 0)
	        {
	          if (WAIT_OBJECT_0 != WaitForSingleObject (mx->event, INFINITE))
	            {
	              result = EINVAL;
		      break;
	            }
	        }
	    }
        }
      else
        {
          pthread_t self = pthread_self();

          if ((PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG(
                       (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
		       (PTW32_INTERLOCKED_LONG) 1,
		       (PTW32_INTERLOCKED_LONG) 0) == 0)
	    {
	      mx->recursive_count = 1;
	      mx->ownerThread = self;
	    }
          else
	    {
	      if (pthread_equal (mx->ownerThread, self))
	        {
	          if (kind == PTHREAD_MUTEX_RECURSIVE)
		    {
		      mx->recursive_count++;
		    }
	          else
		    {
		      result = EDEADLK;
		    }
	        }
	      else
	        {
	          while ((PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_EXCHANGE_LONG(
                                  (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
			          (PTW32_INTERLOCKED_LONG) -1) != 0)
		    {
	              if (WAIT_OBJECT_0 != WaitForSingleObject (mx->event, INFINITE))
		        {
	                  result = EINVAL;
		          break;
		        }
		    }

	          if (0 == result)
		    {
		      mx->recursive_count = 1;
		      mx->ownerThread = self;
		    }
	        }
	    }
        }
    }
  else
    {
      /*
       * Robust types
       * All types record the current owner thread.
       * The mutex is added to a per thread list when ownership is acquired.
       */
      ptw32_robust_state_t* statePtr = &mx->robustNode->stateInconsistent;

      if ((PTW32_INTERLOCKED_LONG)PTW32_ROBUST_NOTRECOVERABLE == PTW32_INTERLOCKED_EXCHANGE_ADD_LONG(
                                                 (PTW32_INTERLOCKED_LONGPTR)statePtr,
                                                 (PTW32_INTERLOCKED_LONG)0))
        {
          result = ENOTRECOVERABLE;
        }
      else
        {
          pthread_t self = pthread_self();

          kind = -kind - 1; /* Convert to non-robust range */
    
          if (PTHREAD_MUTEX_NORMAL == kind)
            {
              if ((PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_EXCHANGE_LONG(
                           (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
                           (PTW32_INTERLOCKED_LONG) 1) != 0)
                {
                  while (0 == (result = ptw32_robust_mutex_inherit(mutex))
                           && (PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_EXCHANGE_LONG(
                                       (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
                                       (PTW32_INTERLOCKED_LONG) -1) != 0)
                    {
                      if (WAIT_OBJECT_0 != WaitForSingleObject (mx->event, INFINITE))
                        {
                          result = EINVAL;
                          break;
                        }
                      if ((PTW32_INTERLOCKED_LONG)PTW32_ROBUST_NOTRECOVERABLE ==
                                  PTW32_INTERLOCKED_EXCHANGE_ADD_LONG(
                                    (PTW32_INTERLOCKED_LONGPTR)statePtr,
                                    (PTW32_INTERLOCKED_LONG)0))
                        {
                          /* Unblock the next thread */
                          SetEvent(mx->event);
                          result = ENOTRECOVERABLE;
                          break;
                        }
                    }
                }
              if (0 == result || EOWNERDEAD == result)
                {
                  /*
                   * Add mutex to the per-thread robust mutex currently-held list.
                   * If the thread terminates, all mutexes in this list will be unlocked.
                   */
                  ptw32_robust_mutex_add(mutex, self);
                }
            }
          else
            {
              if ((PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG(
                           (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
                           (PTW32_INTERLOCKED_LONG) 1,
                           (PTW32_INTERLOCKED_LONG) 0) == 0)
                {
                  mx->recursive_count = 1;
                  /*
                   * Add mutex to the per-thread robust mutex currently-held list.
                   * If the thread terminates, all mutexes in this list will be unlocked.
                   */
                  ptw32_robust_mutex_add(mutex, self);
                }
              else
                {
                  if (pthread_equal (mx->ownerThread, self))
                    {
                      if (PTHREAD_MUTEX_RECURSIVE == kind)
                        {
                          mx->recursive_count++;
                        }
                      else
                        {
                          result = EDEADLK;
                        }
                    }
                  else
                    {
                      while (0 == (result = ptw32_robust_mutex_inherit(mutex))
                               && (PTW32_INTERLOCKED_LONG) PTW32_INTERLOCKED_EXCHANGE_LONG(
                                           (PTW32_INTERLOCKED_LONGPTR) &mx->lock_idx,
                                           (PTW32_INTERLOCKED_LONG) -1) != 0)
                        {
                          if (WAIT_OBJECT_0 != WaitForSingleObject (mx->event, INFINITE))
                            {
                              result = EINVAL;
                              break;
                            }
                          if ((PTW32_INTERLOCKED_LONG)PTW32_ROBUST_NOTRECOVERABLE ==
                                      PTW32_INTERLOCKED_EXCHANGE_ADD_LONG(
                                        (PTW32_INTERLOCKED_LONGPTR)statePtr,
                                        (PTW32_INTERLOCKED_LONG)0))
                            {
                              /* Unblock the next thread */
                              SetEvent(mx->event);
                              result = ENOTRECOVERABLE;
                              break;
                            }
                        }

                      if (0 == result || EOWNERDEAD == result)
                        {
                          mx->recursive_count = 1;
                          /*
                           * Add mutex to the per-thread robust mutex currently-held list.
                           * If the thread terminates, all mutexes in this list will be unlocked.
                           */
                          ptw32_robust_mutex_add(mutex, self);
                        }
                    }
	        }
            }
        }
    }

  return (result);
}