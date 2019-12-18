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
struct TYPE_2__ {void* exitStatus; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTE_EPS_EXIT ; 
 int /*<<< orphan*/  pte_osThreadExit () ; 
 int /*<<< orphan*/  pte_selfThreadKey ; 
 int /*<<< orphan*/  pte_throw (int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_getspecific (int /*<<< orphan*/ ) ; 

void pthread_exit (void *value_ptr)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function terminates the calling thread, returning
    *      the value 'value_ptr' to any joining thread.
    *
    * PARAMETERS
    *      value_ptr
    *              a generic data value (i.e. not the address of a value)
    *
    *
    * DESCRIPTION
    *      This function terminates the calling thread, returning
    *      the value 'value_ptr' to any joining thread.
    *      NOTE: thread should be joinable.
    *
    * RESULTS
    *              N/A
    *
    * ------------------------------------------------------
    */
{
   pte_thread_t * sp;

   /*
    * Don't use pthread_self() to avoid creating an implicit POSIX thread handle
    * unnecessarily.
    */
   sp = (pte_thread_t *) pthread_getspecific (pte_selfThreadKey);

   if (NULL == sp)
   {
      /*
       * A POSIX thread handle was never created. I.e. this is a
       * Win32 thread that has never called a pthreads-win32 routine that
       * required a POSIX handle.
       *
       * Implicit POSIX handles are cleaned up in pte_throw() now.
       */

      /* Terminate thread */
      pte_osThreadExit();

      /* Never reached */
   }

   sp->exitStatus = value_ptr;

   pte_throw (PTE_EPS_EXIT);

   /* Never reached. */
}