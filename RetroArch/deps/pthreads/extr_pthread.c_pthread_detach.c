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
struct TYPE_2__ {scalar_t__ x; scalar_t__ detachState; scalar_t__ state; int /*<<< orphan*/  threadId; int /*<<< orphan*/  cancelLock; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int EINVAL ; 
 int ESRCH ; 
 unsigned char PTE_FALSE ; 
 unsigned char PTE_TRUE ; 
 scalar_t__ PTHREAD_CREATE_DETACHED ; 
 scalar_t__ PThreadStateLast ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osThreadWaitForEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_threadDestroy (scalar_t__) ; 
 int /*<<< orphan*/  pte_thread_reuse_lock ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int pthread_detach (pthread_t thread)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function detaches the given thread.
    *
    * PARAMETERS
    *      thread
    *              an instance of a pthread_t
    *
    *
    * DESCRIPTION
    *      This function detaches the given thread. You may use it to
    *      detach the main thread or to detach a joinable thread.
    *      NOTE:   detached threads cannot be joined;
    *              storage is freed immediately on termination.
    *
    * RESULTS
    *              0               successfully detached the thread,
    *              EINVAL          thread is not a joinable thread,
    *              ENOSPC          a required resource has been exhausted,
    *              ESRCH           no thread could be found for 'thread',
    *
    * ------------------------------------------------------
    */
{
   int result;
   unsigned char destroyIt = PTE_FALSE;
   pte_thread_t * tp = (pte_thread_t *) thread;

   pte_osMutexLock (pte_thread_reuse_lock);

   if (NULL == tp
         || ((pte_thread_t*)thread)->x != tp->x)
      result = ESRCH;
   else if (PTHREAD_CREATE_DETACHED == tp->detachState)
      result = EINVAL;
   else
   {
      /*
       * Joinable pte_thread_t structs are not scavenged until
       * a join or detach is done. The thread may have exited already,
       * but all of the state and locks etc are still there.
       */
      result = 0;

      if (pthread_mutex_lock (&tp->cancelLock) == 0)
      {
         if (tp->state != PThreadStateLast)
            tp->detachState = PTHREAD_CREATE_DETACHED;
         else if (tp->detachState != PTHREAD_CREATE_DETACHED)
         {
            /*
             * Thread is joinable and has exited or is exiting.
             */
            destroyIt = PTE_TRUE;
         }
         (void) pthread_mutex_unlock (&tp->cancelLock);
      }
      else
      {
         /* cancelLock shouldn't fail, but if it does ... */
         result = ESRCH;
      }
   }

   pte_osMutexUnlock(pte_thread_reuse_lock);

   if (result == 0)
   {
      /* Thread is joinable */

      if (destroyIt)
      {
         /* The thread has exited or is exiting but has not been joined or
          * detached. Need to wait in case it's still exiting.
          */
         pte_osThreadWaitForEnd(tp->threadId);

         pte_threadDestroy (thread);
      }
   }

   return (result);
}