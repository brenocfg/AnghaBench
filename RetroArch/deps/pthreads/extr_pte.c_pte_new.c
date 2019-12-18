#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_t ;
struct TYPE_5__ {void* threadLock; void* cancelLock; int /*<<< orphan*/  cancelType; int /*<<< orphan*/  cancelState; int /*<<< orphan*/  detachState; int /*<<< orphan*/  sched_priority; scalar_t__ x; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CANCEL_DEFERRED ; 
 int /*<<< orphan*/  PTHREAD_CANCEL_ENABLE ; 
 int /*<<< orphan*/  PTHREAD_CREATE_JOINABLE ; 
 void* PTHREAD_MUTEX_INITIALIZER ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  pte_osThreadGetMinPriority () ; 
 TYPE_1__* pte_threadReusePop () ; 

pthread_t pte_new (void)
{
   pthread_t nil     = NULL;
   pte_thread_t * tp = NULL;

   /*
    * If there's a reusable pthread_t then use it.
    */
   pthread_t t = pte_threadReusePop ();

   if (NULL != t)
      tp = (pte_thread_t *) t;
   else
   {
      /* No reuse threads available */
      tp = (pte_thread_t *) calloc (1, sizeof(pte_thread_t));

      if (tp == NULL)
         return nil;

      /* ptHandle.p needs to point to it's parent pte_thread_t. */
      t = tp;
      tp->x = 0;
   }

   /* Set default state. */
   tp->sched_priority = pte_osThreadGetMinPriority();

   tp->detachState = PTHREAD_CREATE_JOINABLE;
   tp->cancelState = PTHREAD_CANCEL_ENABLE;
   tp->cancelType = PTHREAD_CANCEL_DEFERRED;
   tp->cancelLock = PTHREAD_MUTEX_INITIALIZER;
   tp->threadLock = PTHREAD_MUTEX_INITIALIZER;

   return t;

}