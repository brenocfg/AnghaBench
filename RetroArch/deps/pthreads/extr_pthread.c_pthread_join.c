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
struct TYPE_2__ {scalar_t__ x; scalar_t__ detachState; void* exitStatus; int /*<<< orphan*/  threadId; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int EDEADLK ; 
 int EINVAL ; 
 int ENOENT ; 
 int ESRCH ; 
 int PTE_OS_INTERRUPTED ; 
 int PTE_OS_OK ; 
 scalar_t__ PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 int pte_osThreadWaitForEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_thread_reuse_lock ; 
 int pthread_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pthread_self () ; 

int pthread_join (pthread_t thread, void **value_ptr)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function waits for 'thread' to terminate and
    *      returns the thread's exit value if 'value_ptr' is not
    *      NULL. This also detaches the thread on successful
    *      completion.
    *
    * PARAMETERS
    *      thread
    *              an instance of pthread_t
    *
    *      value_ptr
    *              pointer to an instance of pointer to void
    *
    *
    * DESCRIPTION
    *      This function waits for 'thread' to terminate and
    *      returns the thread's exit value if 'value_ptr' is not
    *      NULL. This also detaches the thread on successful
    *      completion.
    *      NOTE:   detached threads cannot be joined or canceled
    *
    * RESULTS
    *              0               'thread' has completed
    *              EINVAL          thread is not a joinable thread,
    *              ESRCH           no thread could be found with ID 'thread',
    *              ENOENT          thread couldn't find it's own valid handle,
    *              EDEADLK         attempt to join thread with self
    *
    * ------------------------------------------------------
    */
{
   int result;
   pthread_t self;
   pte_thread_t * tp = (pte_thread_t *) thread;

   pte_osMutexLock (pte_thread_reuse_lock);

   if (NULL == tp
         || ((pte_thread_t*)thread)->x != tp->x)
      result = ESRCH;
   else if (PTHREAD_CREATE_DETACHED == tp->detachState)
      result = EINVAL;
   else
      result = 0;

   pte_osMutexUnlock(pte_thread_reuse_lock);

   if (result == 0)
   {
      /*
       * The target thread is joinable and can't be reused before we join it.
       */
      self = pthread_self();

      if (NULL == self)
         result = ENOENT;
      else if (pthread_equal (self, thread))
         result = EDEADLK;
      else
      {
         /*
          * Pthread_join is a cancelation point.
          * If we are canceled then our target thread must not be
          * detached (destroyed). This is guarranteed because
          * pthreadCancelableWait will not return if we
          * are canceled.
          */

         result = pte_osThreadWaitForEnd(tp->threadId);

         if (PTE_OS_OK == result)
         {
            if (value_ptr != NULL)
               *value_ptr = tp->exitStatus;

            /*
             * The result of making multiple simultaneous calls to
             * pthread_join() or pthread_detach() specifying the same
             * target is undefined.
             */
            result = pthread_detach (thread);
         }
         /* Call was cancelled, but still return success (per spec) */
         else if (result == PTE_OS_INTERRUPTED)
            result = 0;
         else
            result = ESRCH;
      }
   }

   return (result);
}