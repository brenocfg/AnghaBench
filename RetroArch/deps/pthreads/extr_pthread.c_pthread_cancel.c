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
typedef  int /*<<< orphan*/ * pthread_t ;
struct TYPE_2__ {scalar_t__ cancelType; scalar_t__ cancelState; scalar_t__ state; int /*<<< orphan*/  cancelLock; int /*<<< orphan*/  threadId; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  PTE_EPS_CANCEL ; 
 scalar_t__ PTE_OS_OK ; 
 scalar_t__ PTHREAD_CANCEL_ASYNCHRONOUS ; 
 scalar_t__ PTHREAD_CANCEL_DISABLE ; 
 scalar_t__ PTHREAD_CANCEL_ENABLE ; 
 scalar_t__ PThreadStateCancelPending ; 
 scalar_t__ PThreadStateCanceling ; 
 scalar_t__ pte_osThreadCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_throw (int /*<<< orphan*/ ) ; 
 int pthread_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_kill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pthread_self () ; 

int pthread_cancel (pthread_t thread)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function requests cancellation of 'thread'.
    *
    * PARAMETERS
    *      thread
    *              reference to an instance of pthread_t
    *
    *
    * DESCRIPTION
    *      This function requests cancellation of 'thread'.
    *      NOTE: cancellation is asynchronous; use pthread_join to
    *                wait for termination of 'thread' if necessary.
    *
    * RESULTS
    *              0               successfully requested cancellation,
    *              ESRCH           no thread found corresponding to 'thread',
    *              ENOMEM          implicit self thread create failed.
    * ------------------------------------------------------
    */
{
   int result;
   int cancel_self;
   pthread_t self;
   pte_thread_t * tp;

   result = pthread_kill (thread, 0);

   if (0 != result)
      return result;

   if ((self = pthread_self ()) == NULL)
      return ENOMEM;

   /*
    * FIXME!!
    *
    * Can a thread cancel itself?
    *
    * The standard doesn't
    * specify an error to be returned if the target
    * thread is itself.
    *
    * If it may, then we need to ensure that a thread can't
    * deadlock itself trying to cancel itself asyncronously
    * (pthread_cancel is required to be an async-cancel
    * safe function).
    */
   cancel_self = pthread_equal (thread, self);

   tp = (pte_thread_t *) thread;

   /*
    * Lock for async-cancel safety.
    */
   (void) pthread_mutex_lock (&tp->cancelLock);

   if (tp->cancelType == PTHREAD_CANCEL_ASYNCHRONOUS
         && tp->cancelState == PTHREAD_CANCEL_ENABLE
         && tp->state < PThreadStateCanceling)
   {
      if (cancel_self)
      {
         tp->state = PThreadStateCanceling;
         tp->cancelState = PTHREAD_CANCEL_DISABLE;

         (void) pthread_mutex_unlock (&tp->cancelLock);
         pte_throw (PTE_EPS_CANCEL);

         /* Never reached */
      }
      else
      {
         /*
          * We don't support asynchronous cancellation for thread other than ourselves.
          * as it requires significant platform and OS specific functionality (see below).
          *
          * We should never get here, as we don't allow the cancellability type to be
          * sent to async.
          *
          * If you really wanted to implement async cancellation, you would probably need to
          * do something like the Win32 implement did, which is:
          *   1. Suspend the target thread.
          *   2. Replace the PC for the target thread to a routine that throws an exception
          *      or does a longjmp, depending on cleanup method.
          *   3. Resume the target thread.
          *
          * Note that most of the async cancellation code is still in here if anyone
          * wanted to add the OS/platform specific stuff.
          */
         (void) pthread_mutex_unlock (&tp->cancelLock);

         result = EPERM;

      }
   }
   else
   {
      /*
       * Set for deferred cancellation.
       */
      if (tp->state < PThreadStateCancelPending)
      {
         tp->state = PThreadStateCancelPending;

         if (pte_osThreadCancel(tp->threadId) != PTE_OS_OK)
            result = ESRCH;
      }
      else if (tp->state >= PThreadStateCanceling)
         result = ESRCH;

      (void) pthread_mutex_unlock (&tp->cancelLock);
   }

   return (result);
}