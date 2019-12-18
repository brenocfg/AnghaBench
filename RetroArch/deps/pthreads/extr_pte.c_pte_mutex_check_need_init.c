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
typedef  int /*<<< orphan*/ * pthread_mutex_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * PTHREAD_ERRORCHECK_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/ * PTHREAD_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/ * PTHREAD_RECURSIVE_MUTEX_INITIALIZER ; 
 int /*<<< orphan*/  pte_errorcheck_mutexattr ; 
 int /*<<< orphan*/  pte_mutex_test_init_lock ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_recursive_mutexattr ; 
 int pthread_mutex_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int pte_mutex_check_need_init (pthread_mutex_t * mutex)
{
   register int result = 0;
   register pthread_mutex_t mtx;

   /*
    * The following guarded test is specifically for statically
    * initialised mutexes (via PTHREAD_MUTEX_INITIALIZER).
    *
    * Note that by not providing this synchronisation we risk
    * introducing race conditions into applications which are
    * correctly written.
    *
    * Approach
    * --------
    * We know that static mutexes will not be PROCESS_SHARED
    * so we can serialise access to internal state using
    * critical sections rather than mutexes.
    *
    * If using a single global lock slows applications down too much,
    * multiple global locks could be created and hashed on some random
    * value associated with each mutex, the pointer perhaps. At a guess,
    * a good value for the optimal number of global locks might be
    * the number of processors + 1.
    *
    */


   pte_osMutexLock (pte_mutex_test_init_lock);

   /*
    * We got here possibly under race
    * conditions. Check again inside the critical section
    * and only initialise if the mutex is valid (not been destroyed).
    * If a static mutex has been destroyed, the application can
    * re-initialise it only by calling pthread_mutex_init()
    * explicitly.
    */
   mtx = *mutex;

   if (mtx == PTHREAD_MUTEX_INITIALIZER)
      result = pthread_mutex_init (mutex, NULL);
   else if (mtx == PTHREAD_RECURSIVE_MUTEX_INITIALIZER)
      result = pthread_mutex_init (mutex, &pte_recursive_mutexattr);
   else if (mtx == PTHREAD_ERRORCHECK_MUTEX_INITIALIZER)
      result = pthread_mutex_init (mutex, &pte_errorcheck_mutexattr);
   /*
    * The mutex has been destroyed while we were waiting to
    * initialise it, so the operation that caused the
    * auto-initialisation should fail.
    */
   else if (mtx == NULL)
      result = EINVAL;

   pte_osMutexUnlock(pte_mutex_test_init_lock);

   return (result);
}