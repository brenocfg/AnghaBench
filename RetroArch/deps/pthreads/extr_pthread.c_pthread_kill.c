#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pthread_t ;
struct TYPE_2__ {scalar_t__ x; scalar_t__ threadId; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_thread_reuse_lock ; 

int pthread_kill (pthread_t thread, int sig)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function requests that a signal be delivered to the
    *      specified thread. If sig is zero, error checking is
    *      performed but no signal is actually sent such that this
    *      function can be used to check for a valid thread ID.
    *
    * PARAMETERS
    *      thread  reference to an instances of pthread_t
    *      sig     signal. Currently only a value of 0 is supported.
    *
    *
    * DESCRIPTION
    *      This function requests that a signal be delivered to the
    *      specified thread. If sig is zero, error checking is
    *      performed but no signal is actually sent such that this
    *      function can be used to check for a valid thread ID.
    *
    * RESULTS
    *              ESRCH           the thread is not a valid thread ID,
    *              EINVAL          the value of the signal is invalid
    *                              or unsupported.
    *              0               the signal was successfully sent.
    *
    * ------------------------------------------------------
    */
{
   int result = 0;
   pte_thread_t * tp;

   pte_osMutexLock (pte_thread_reuse_lock);

   tp = (pte_thread_t *) thread;

   if (NULL == tp
         || ((pte_thread_t*)thread)->x != tp->x
         || 0 == tp->threadId)
      result = ESRCH;

   pte_osMutexUnlock(pte_thread_reuse_lock);

   /*
    * Currently does not support any signals.
    */
   if (0 == result && 0 != sig)
      result = EINVAL;

   return result;
}