#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * pthread_t ;
typedef  TYPE_2__* pthread_attr_t ;
struct TYPE_10__ {int sched_priority; scalar_t__ threadId; int /*<<< orphan*/  threadLock; int /*<<< orphan*/ * keys; int /*<<< orphan*/  state; int /*<<< orphan*/  detachState; } ;
typedef  TYPE_3__ pte_thread_t ;
typedef  scalar_t__ pte_osResult ;
struct TYPE_11__ {void* (* start ) (void*) ;void* arg; int /*<<< orphan*/ * tid; } ;
typedef  TYPE_4__ ThreadParms ;
struct TYPE_8__ {int sched_priority; } ;
struct TYPE_9__ {long stacksize; scalar_t__ inheritsched; TYPE_1__ param; int /*<<< orphan*/  detachstate; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ PTE_OS_OK ; 
 int PTE_TRUE ; 
 scalar_t__ PTHREAD_INHERIT_SCHED ; 
 long PTHREAD_STACK_MIN ; 
 int /*<<< orphan*/  PThreadStateInitial ; 
 int /*<<< orphan*/  PThreadStateSuspended ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/ * pte_new () ; 
 scalar_t__ pte_osThreadCreate (int /*<<< orphan*/ ,long,int,TYPE_4__*,scalar_t__*) ; 
 int pte_osThreadGetMaxPriority () ; 
 int pte_osThreadGetMinPriority () ; 
 int /*<<< orphan*/  pte_osThreadStart (scalar_t__) ; 
 int /*<<< orphan*/  pte_threadDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_threadStart ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pthread_self () ; 

int pthread_create (pthread_t * tid,
                const pthread_attr_t * attr,
                void *(*start) (void *), void *arg)
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function creates a thread running the start function,
 *      passing it the parameter value, 'arg'. The 'attr'
 *      argument specifies optional creation attributes.
 *      The identity of the new thread is returned
 *      via 'tid', which should not be NULL.
 *
 * PARAMETERS
 *      tid
 *              pointer to an instance of pthread_t
 *
 *      attr
 *              optional pointer to an instance of pthread_attr_t
 *
 *      start
 *              pointer to the starting routine for the new thread
 *
 *      arg
 *              optional parameter passed to 'start'
 *
 *
 * DESCRIPTION
 *      This function creates a thread running the start function,
 *      passing it the parameter value, 'arg'. The 'attr'
 *      argument specifies optional creation attributes.
 *      The identity of the new thread is returned
 *      via 'tid', which should not be the NULL pointer.
 *
 * RESULTS
 *              0               successfully created thread,
 *              EINVAL          attr invalid,
 *              EAGAIN          insufficient resources.
 *
 * ------------------------------------------------------
 */
{
   pthread_t thread;
   pte_thread_t * tp;
   int result = EAGAIN;
   int run = PTE_TRUE;
   ThreadParms *parms = NULL;
   long stackSize;
   int priority = 0;
   pthread_t self;
   pte_osResult osResult;
   register pthread_attr_t a = NULL;

   /*
    * Before doing anything, check that tid can be stored through
    * without invoking a memory protection error (segfault).
    * Make sure that the assignment below can't be optimised out by the compiler.
    * This is assured by conditionally assigning *tid again at the end.
    */

   if (attr != NULL)
      a = *attr;

   if ((thread = pte_new ()) == NULL)
      goto FAIL0;

   tp = (pte_thread_t *) thread;

   priority = tp->sched_priority;

   if ((parms = (ThreadParms *) malloc (sizeof (*parms))) == NULL)
      goto FAIL0;

   parms->tid   = thread;
   parms->start = start;
   parms->arg   = arg;

   if (a != NULL)
   {
      stackSize = a->stacksize;
      tp->detachState = a->detachstate;
      priority = a->param.sched_priority;

      if ( (priority > pte_osThreadGetMaxPriority()) ||
            (priority < pte_osThreadGetMinPriority()) )
      {
         result = EINVAL;
         goto FAIL0;
      }

      /* Everything else */

      /*
       * Thread priority must be set to a valid system level
       * without altering the value set by pthread_attr_setschedparam().
       */

      if (PTHREAD_INHERIT_SCHED == a->inheritsched)
      {
         /*
          * If the thread that called pthread_create() is an OS thread
          * then the inherited priority could be the result of a temporary
          * system adjustment. This is not the case for POSIX threads.
          */
         self = pthread_self ();
         priority = ((pte_thread_t *) self)->sched_priority;
      }


   }
   else
   {
      /*
       * Default stackSize
       */
      stackSize = PTHREAD_STACK_MIN;

   }

   tp->state = run ? PThreadStateInitial : PThreadStateSuspended;

   tp->keys  = NULL;

   /*
    * Threads must be started in suspended mode and resumed if necessary
    * after _beginthreadex returns us the handle. Otherwise we set up a
    * race condition between the creating and the created threads.
    * Note that we also retain a local copy of the handle for use
    * by us in case thread.p->threadH gets NULLed later but before we've
    * finished with it here.
    */
   result = pthread_mutex_lock (&tp->threadLock);

   if (result == 0)
   {
      /*
       * Must record the thread's sched_priority as given,
       * not as finally adjusted.
       */
      tp->sched_priority = priority;

      (void) pthread_mutex_unlock (&tp->threadLock);
   }

   osResult = pte_osThreadCreate(pte_threadStart,
         stackSize,
         priority,
         parms,
         &(tp->threadId));

   if (osResult == PTE_OS_OK)
   {
      pte_osThreadStart(tp->threadId);
      result = 0;
   }
   else
   {
      tp->threadId = 0;
      result = EAGAIN;
      goto FAIL0;
   }

   /*
    * Fall Through Intentionally
    */

   /*
    * ------------
    * Failure Code
    * ------------
    */

FAIL0:
   if (result != 0)
   {

      pte_threadDestroy (thread);
      tp = NULL;

      if (parms != NULL)
         free (parms);
   }
   else
   {
      if (tid != NULL)
         *tid = thread;
   }

   return (result);
}