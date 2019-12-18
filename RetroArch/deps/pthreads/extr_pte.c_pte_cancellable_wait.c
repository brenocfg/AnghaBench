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
struct TYPE_2__ {scalar_t__ cancelState; int /*<<< orphan*/  cancelLock; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ pte_thread_t ;
typedef  int /*<<< orphan*/  pte_osSemaphoreHandle ;
typedef  int pte_osResult ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PTE_EPS_CANCEL ; 
#define  PTE_OS_INTERRUPTED 130 
#define  PTE_OS_OK 129 
#define  PTE_OS_TIMEOUT 128 
 scalar_t__ PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  PThreadStateCanceling ; 
 int pte_osSemaphoreCancellablePend (int /*<<< orphan*/ ,unsigned int*) ; 
 int pte_osSemaphorePend (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  pte_throw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_self () ; 

int pte_cancellable_wait (pte_osSemaphoreHandle semHandle, unsigned int* timeout)
{
   pte_osResult osResult;
   int result        = EINVAL;
   int cancelEnabled = 0;
   pthread_t self    = pthread_self();
   pte_thread_t *sp  = (pte_thread_t *) self;

   if (sp)
   {
      /*
       * Get cancelEvent handle
       */
      if (sp->cancelState == PTHREAD_CANCEL_ENABLE)
         cancelEnabled = 1;
   }


   if (cancelEnabled)
      osResult = pte_osSemaphoreCancellablePend(semHandle, timeout);
   else
      osResult = pte_osSemaphorePend(semHandle, timeout);

   switch (osResult)
   {
      case PTE_OS_OK:
         result = 0;
         break;

      case PTE_OS_TIMEOUT:
         result = ETIMEDOUT;
         break;

      case PTE_OS_INTERRUPTED:
         if (sp)
         {
            /*
             * Should handle POSIX and implicit POSIX threads..
             * Make sure we haven't been async-canceled in the meantime.
             */
            (void) pthread_mutex_lock (&sp->cancelLock);
            if (sp->state < PThreadStateCanceling)
            {
               sp->state = PThreadStateCanceling;
               sp->cancelState = PTHREAD_CANCEL_DISABLE;
               (void) pthread_mutex_unlock (&sp->cancelLock);
               pte_throw (PTE_EPS_CANCEL);

               /* Never reached */
            }
            (void) pthread_mutex_unlock (&sp->cancelLock);
         }
         break;
      default:
         result = EINVAL;
   }

   return (result);
}