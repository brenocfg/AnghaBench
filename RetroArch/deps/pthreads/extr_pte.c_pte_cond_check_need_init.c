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
typedef  int /*<<< orphan*/ * pthread_cond_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * PTHREAD_COND_INITIALIZER ; 
 int /*<<< orphan*/  pte_cond_test_init_lock ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 int pthread_cond_init (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int pte_cond_check_need_init (pthread_cond_t * cond)
{
   int result = 0;

   /*
    * The following guarded test is specifically for statically
    * initialised condition variables (via PTHREAD_OBJECT_INITIALIZER).
    *
    * Note that by not providing this synchronisation we risk
    * introducing race conditions into applications which are
    * correctly written.
    *
    * Approach
    * --------
    * We know that static condition variables will not be PROCESS_SHARED
    * so we can serialise access to internal state using
    * Win32 Critical Sections rather than Win32 Mutexes.
    *
    * If using a single global lock slows applications down too much,
    * multiple global locks could be created and hashed on some random
    * value associated with each mutex, the pointer perhaps. At a guess,
    * a good value for the optimal number of global locks might be
    * the number of processors + 1.
    *
    */


   pte_osMutexLock (pte_cond_test_init_lock);

   /*
    * We got here possibly under race
    * conditions. Check again inside the critical section.
    * If a static cv has been destroyed, the application can
    * re-initialise it only by calling pthread_cond_init()
    * explicitly.
    */
   if (*cond == PTHREAD_COND_INITIALIZER)
      result = pthread_cond_init (cond, NULL);
   /*
    * The cv has been destroyed while we were waiting to
    * initialise it, so the operation that caused the
    * auto-initialisation should fail.
    */
   else if (*cond == NULL)
      result = EINVAL;


   pte_osMutexUnlock(pte_cond_test_init_lock);

   return result;
}