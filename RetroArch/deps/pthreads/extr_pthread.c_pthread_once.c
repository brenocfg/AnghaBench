#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; scalar_t__ semaphore; int /*<<< orphan*/  numSemaphoreUsers; } ;
typedef  TYPE_1__ pthread_once_t ;
typedef  scalar_t__ pte_osSemaphoreHandle ;

/* Variables and functions */
 int EINVAL ; 
 int PTE_ATOMIC_COMPARE_EXCHANGE (int*,int,int) ; 
 scalar_t__ PTE_ATOMIC_DECREMENT (int /*<<< orphan*/ *) ; 
 scalar_t__ PTE_ATOMIC_EXCHANGE (int*,int) ; 
 scalar_t__ PTE_ATOMIC_EXCHANGE_ADD (int*,long) ; 
 int /*<<< orphan*/  PTE_ATOMIC_INCREMENT (int /*<<< orphan*/ *) ; 
 int PTE_ONCE_DONE ; 
 int PTE_ONCE_INIT ; 
 scalar_t__ PTE_ONCE_STARTED ; 
 int /*<<< orphan*/  pte_once_init_routine_cleanup ; 
 int /*<<< orphan*/  pte_osSemaphoreCreate (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pte_osSemaphoreDelete (scalar_t__) ; 
 int /*<<< orphan*/  pte_osSemaphorePend (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_osSemaphorePost (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,void*) ; 
 void stub1 () ; 

int pthread_once (pthread_once_t * once_control, void (*init_routine) (void))
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      If any thread in a process  with  a  once_control  parameter
 *      makes  a  call to pthread_once(), the first call will summon
 *      the init_routine(), but  subsequent  calls  will  not. The
 *      once_control  parameter  determines  whether  the associated
 *      initialization routine has been called.  The  init_routine()
 *      is complete upon return of pthread_once().
 *      This function guarantees that one and only one thread
 *      executes the initialization routine, init_routine when
 *      access is controlled by the pthread_once_t control
 *      key.
 *
 *      pthread_once() is not a cancelation point, but the init_routine
 *      can be. If it's cancelled then the effect on the once_control is
 *      as if pthread_once had never been entered.
 *
 *
 * PARAMETERS
 *      once_control
 *              pointer to an instance of pthread_once_t
 *
 *      init_routine
 *              pointer to an initialization routine
 *
 *
 * DESCRIPTION
 *      See above.
 *
 * RESULTS
 *              0               success,
 *              EINVAL          once_control or init_routine is NULL
 *
 * ------------------------------------------------------
 */
{
   int result;
   int state;
   pte_osSemaphoreHandle sema;

   if (once_control == NULL || init_routine == NULL)
   {
      result = EINVAL;
      goto FAIL0;
   }
   else
   {
      result = 0;
   }

   while ((state =
            PTE_ATOMIC_COMPARE_EXCHANGE(&once_control->state,
               PTE_ONCE_STARTED,
               PTE_ONCE_INIT))
         != PTE_ONCE_DONE)
   {
      if (PTE_ONCE_INIT == state)
      {


         pthread_cleanup_push(pte_once_init_routine_cleanup, (void *) once_control);
         (*init_routine)();
         pthread_cleanup_pop(0);

         (void) PTE_ATOMIC_EXCHANGE(&once_control->state,PTE_ONCE_DONE);

         /*
          * we didn't create the semaphore.
          * it is only there if there is someone waiting.
          */
         if (PTE_ATOMIC_EXCHANGE_ADD((int*)&once_control->semaphore, 0L)) /* MBR fence */
            pte_osSemaphorePost((pte_osSemaphoreHandle) once_control->semaphore,once_control->numSemaphoreUsers);
      }
      else
      {
         PTE_ATOMIC_INCREMENT(&once_control->numSemaphoreUsers);

         if (!PTE_ATOMIC_EXCHANGE_ADD((int*)&once_control->semaphore, 0L)) /* MBR fence */
         {
            pte_osSemaphoreCreate(0, (pte_osSemaphoreHandle*) &sema);

            if (PTE_ATOMIC_COMPARE_EXCHANGE((int *) &once_control->semaphore,
                     (int) sema,
                     0))
               pte_osSemaphoreDelete((pte_osSemaphoreHandle)sema);
         }

         /*
          * Check 'state' again in case the initting thread has finished or
          * cancelled and left before seeing that there was a semaphore.
          */
         if (PTE_ATOMIC_EXCHANGE_ADD(&once_control->state, 0L) == PTE_ONCE_STARTED)
            pte_osSemaphorePend((pte_osSemaphoreHandle) once_control->semaphore,NULL);

         if (0 == PTE_ATOMIC_DECREMENT(&once_control->numSemaphoreUsers))
         {
            /* we were last */
            if ((sema =
                     (pte_osSemaphoreHandle) PTE_ATOMIC_EXCHANGE((int *) &once_control->semaphore,0)))
               pte_osSemaphoreDelete(sema);
         }
      }
   }

   /*
    * ------------
    * Failure Code
    * ------------
    */
FAIL0:
   return (result);
}