#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_cond_t ;
struct TYPE_4__ {int* resultPtr; int /*<<< orphan*/ * mutexPtr; TYPE_1__* cv; } ;
typedef  TYPE_2__ pte_cond_wait_cleanup_args_t ;
struct TYPE_3__ {int nWaitersToUnblock; int nWaitersGone; int nWaitersBlocked; int /*<<< orphan*/  semBlockLock; int /*<<< orphan*/  mtxUnblockLock; } ;

/* Variables and functions */
 int INT_MAX ; 
 int errno ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pte_cond_wait_cleanup (void *args)
{
   pte_cond_wait_cleanup_args_t *cleanup_args =
      (pte_cond_wait_cleanup_args_t *) args;
   pthread_cond_t cv = cleanup_args->cv;
   int *resultPtr = cleanup_args->resultPtr;
   int nSignalsWasLeft;
   int result;

   /*
    * Whether we got here as a result of signal/broadcast or because of
    * timeout on wait or thread cancellation we indicate that we are no
    * longer waiting. The waiter is responsible for adjusting waiters
    * (to)unblock(ed) counts (protected by unblock lock).
    */
   if ((result = pthread_mutex_lock (&(cv->mtxUnblockLock))) != 0)
   {
      *resultPtr = result;
      return;
   }

   if (0 != (nSignalsWasLeft = cv->nWaitersToUnblock))
   {
      --(cv->nWaitersToUnblock);
   }
   else if (INT_MAX / 2 == ++(cv->nWaitersGone))
   {
      /* Use the non-cancellable version of sem_wait() */
      //      if (sem_wait_nocancel (&(cv->semBlockLock)) != 0)
      if (sem_wait (&(cv->semBlockLock)) != 0)
      {
         *resultPtr = errno;
         /*
          * This is a fatal error for this CV,
          * so we deliberately don't unlock
          * cv->mtxUnblockLock before returning.
          */
         return;
      }
      cv->nWaitersBlocked -= cv->nWaitersGone;
      if (sem_post (&(cv->semBlockLock)) != 0)
      {
         *resultPtr = errno;
         /*
          * This is a fatal error for this CV,
          * so we deliberately don't unlock
          * cv->mtxUnblockLock before returning.
          */
         return;
      }
      cv->nWaitersGone = 0;
   }

   if ((result = pthread_mutex_unlock (&(cv->mtxUnblockLock))) != 0)
   {
      *resultPtr = result;
      return;
   }

   if (1 == nSignalsWasLeft)
   {
      if (sem_post (&(cv->semBlockLock)) != 0)
      {
         *resultPtr = errno;
         return;
      }
   }

   /*
    * XSH: Upon successful return, the mutex has been locked and is owned
    * by the calling thread.
    */
   if ((result = pthread_mutex_lock (cleanup_args->mutexPtr)) != 0)
      *resultPtr = result;
}