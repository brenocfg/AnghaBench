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
struct TYPE_5__ {int implicit; scalar_t__ sched_priority; int /*<<< orphan*/  threadId; int /*<<< orphan*/  detachState; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 TYPE_1__* pte_new () ; 
 int /*<<< orphan*/  pte_osThreadGetHandle () ; 
 int /*<<< orphan*/  pte_selfThreadKey ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,void*) ; 

pthread_t pthread_self (void)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function returns a reference to the current running
    *      thread.
    *
    * PARAMETERS
    *      N/A
    *
    *
    * DESCRIPTION
    *      This function returns a reference to the current running
    *      thread.
    *
    * RESULTS
    *              pthread_t       reference to the current thread
    *
    * ------------------------------------------------------
    */
{
   pthread_t self;
   pte_thread_t * sp;

   sp = (pte_thread_t *) pthread_getspecific (pte_selfThreadKey);

   if (sp != NULL)
      self = sp;
   else
   {
      /*
       * Need to create an implicit 'self' for the currently
       * executing thread.
       *
       * Note that this is a potential memory leak as there is
       * no way to free the memory and any resources allocated
       * by pte_new!
       */
      self = pte_new ();
      sp = (pte_thread_t *) self;

      if (sp != NULL)
      {
         /*
          * This is a non-POSIX thread which has chosen to call
          * a POSIX threads function for some reason. We assume that
          * it isn't joinable, but we do assume that it's
          * (deferred) cancelable.
          */
         sp->implicit = 1;
         sp->detachState = PTHREAD_CREATE_DETACHED;

         sp->threadId = pte_osThreadGetHandle();
         /*
          * No need to explicitly serialise access to sched_priority
          * because the new handle is not yet public.
          */
         sp->sched_priority = 0;

         pthread_setspecific (pte_selfThreadKey, (void *) sp);
      }
   }

   return (self);
}