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
struct TYPE_2__ {int /*<<< orphan*/  start_mark; int /*<<< orphan*/  exitStatus; scalar_t__ implicit; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
#define  PTE_EPS_CANCEL 129 
#define  PTE_EPS_EXIT 128 
 int /*<<< orphan*/  PTHREAD_CANCELED ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pte_osThreadExit (void*) ; 
 int /*<<< orphan*/  pte_pop_cleanup_all (int) ; 
 int /*<<< orphan*/  pte_selfThreadKey ; 
 int /*<<< orphan*/  pte_thread_detach_and_exit_np () ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 

void pte_throw (unsigned int exception)
{
   /*
    * Don't use pthread_self() to avoid creating an implicit POSIX thread handle
    * unnecessarily.
    */
   pte_thread_t * sp = (pte_thread_t *) pthread_getspecific (pte_selfThreadKey);


   /* Should never enter here */
   if (exception != PTE_EPS_CANCEL && exception != PTE_EPS_EXIT)
      exit (1);

   if (NULL == sp || sp->implicit)
   {
      /*
       * We're inside a non-POSIX initialised OS thread
       * so there is no point to jump or throw back to. Just do an
       * explicit thread exit here after cleaning up POSIX
       * residue (i.e. cleanup handlers, POSIX thread handle etc).
       */
      unsigned exitCode = 0;

      switch (exception)
      {
         case PTE_EPS_CANCEL:
            exitCode = (unsigned) PTHREAD_CANCELED;
            break;
         case PTE_EPS_EXIT:
            exitCode = (unsigned) sp->exitStatus;;
            break;
      }

      pte_thread_detach_and_exit_np ();

#if 0
      pte_osThreadExit((void*)exitCode);
#endif
   }

   pte_pop_cleanup_all (1);
   longjmp (sp->start_mark, exception);

   /* Never reached */
}