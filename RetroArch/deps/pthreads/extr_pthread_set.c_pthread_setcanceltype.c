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
struct TYPE_2__ {int cancelType; scalar_t__ cancelState; int /*<<< orphan*/  cancelLock; int /*<<< orphan*/  state; int /*<<< orphan*/  threadId; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  PTE_EPS_CANCEL ; 
 scalar_t__ PTE_OS_INTERRUPTED ; 
 int PTHREAD_CANCEL_ASYNCHRONOUS ; 
 int PTHREAD_CANCEL_DEFERRED ; 
 scalar_t__ PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  PThreadStateCanceling ; 
 scalar_t__ pte_osThreadCheckCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_throw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_self () ; 

int pthread_setcanceltype (int type, int *oldtype)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function atomically sets the calling thread's
    *      cancelability type to 'type' and returns the previous
    *      cancelability type at the location referenced by
    *      'oldtype'
    *
    * PARAMETERS
    *      type,
    *      oldtype
    *              PTHREAD_CANCEL_DEFERRED
    *                      only deferred cancelation is allowed,
    *
    *              PTHREAD_CANCEL_ASYNCHRONOUS
    *                      Asynchronous cancellation is allowed
    *
    *
    * DESCRIPTION
    *      This function atomically sets the calling thread's
    *      cancelability type to 'type' and returns the previous
    *      cancelability type at the location referenced by
    *      'oldtype'
    *
    *      NOTES:
    *      1)      Use with caution; most code is not safe for use
    *              with asynchronous cancelability.
    *
    * COMPATIBILITY ADDITIONS
    *      If 'oldtype' is NULL then the previous type is not returned
    *      but the function still succeeds. (Solaris)
    *
    * RESULTS
    *              0               successfully set cancelability type,
    *              EINVAL          'type' is invalid
    *              EPERM           Async cancellation is not supported.
    *
    * ------------------------------------------------------
    */
{
   int result = 0;
   pthread_t self = pthread_self ();
   pte_thread_t * sp = (pte_thread_t *) self;

#ifndef PTE_SUPPORT_ASYNC_CANCEL
   if (type == PTHREAD_CANCEL_ASYNCHRONOUS)
   {
      /* Async cancellation is not supported at this time.  See notes in
       * pthread_cancel.
       */
      return EPERM;
   }
#endif /* PTE_SUPPORT_ASYNC_CANCEL */

   if (sp == NULL
         || (type != PTHREAD_CANCEL_DEFERRED
            && type != PTHREAD_CANCEL_ASYNCHRONOUS))
      return EINVAL;

   /*
    * Lock for async-cancel safety.
    */
   (void) pthread_mutex_lock (&sp->cancelLock);

   if (oldtype != NULL)
      *oldtype = sp->cancelType;

   sp->cancelType = type;

   /*
    * Check if there is a pending asynchronous cancel
    */

   if (sp->cancelState == PTHREAD_CANCEL_ENABLE
         && (type == PTHREAD_CANCEL_ASYNCHRONOUS)
         && (pte_osThreadCheckCancel(sp->threadId) == PTE_OS_INTERRUPTED) )
   {
      sp->state = PThreadStateCanceling;
      sp->cancelState = PTHREAD_CANCEL_DISABLE;
      (void) pthread_mutex_unlock (&sp->cancelLock);
      pte_throw (PTE_EPS_CANCEL);

      /* Never reached */
   }

   (void) pthread_mutex_unlock (&sp->cancelLock);

   return (result);
}