#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pthread_t ;
struct TYPE_5__ {void* exitStatus; int /*<<< orphan*/  start_mark; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ pte_thread_t ;
struct TYPE_6__ {void* (* start ) (void*) ;void* arg; scalar_t__ tid; } ;
typedef  TYPE_2__ ThreadParms ;

/* Variables and functions */
#define  PTE_EPS_CANCEL 129 
#define  PTE_EPS_EXIT 128 
 void* PTHREAD_CANCELED ; 
 int /*<<< orphan*/  PThreadStateRunning ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  pte_selfThreadKey ; 
 int /*<<< orphan*/  pte_thread_detach_and_exit_np () ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int setjmp (int /*<<< orphan*/ ) ; 
 void* stub1 (void*) ; 

int pte_threadStart (void *vthreadParms)
{
   ThreadParms * threadParms = (ThreadParms *) vthreadParms;
   void *(*start) (void *);
   void * arg;


   int setjmp_rc;

   void * status    = (void *) 0;

   pthread_t self   = threadParms->tid;
   pte_thread_t *sp = (pte_thread_t *) self;
   start = threadParms->start;
   arg = threadParms->arg;

#if 0
   free (threadParms);
#endif

   pthread_setspecific (pte_selfThreadKey, sp);

   sp->state = PThreadStateRunning;

   setjmp_rc = setjmp (sp->start_mark);


   /*
    * Run the caller's routine;
    */
   if (0 == setjmp_rc)
      sp->exitStatus = status = (*start) (arg);
   else
   {
      switch (setjmp_rc)
      {
         case PTE_EPS_CANCEL:
            status = sp->exitStatus = PTHREAD_CANCELED;
            break;
         case PTE_EPS_EXIT:
            status = sp->exitStatus;
            break;
         default:
            status = sp->exitStatus = PTHREAD_CANCELED;
            break;
      }
   }

   /*
    * We need to cleanup the pthread now if we have
    * been statically linked, in which case the cleanup
    * in dllMain won't get done. Joinable threads will
    * only be partially cleaned up and must be fully cleaned
    * up by pthread_join() or pthread_detach().
    *
    * Note: if this library has been statically linked,
    * implicitly created pthreads (those created
    * for OS threads which have called pthreads routines)
    * must be cleaned up explicitly by the application
    * (by calling pte_thread_detach_np()).
    */
   (void) pte_thread_detach_and_exit_np ();

   //pte_osThreadExit(status);

   /*
    * Never reached.
    */

   return (unsigned) status;
}