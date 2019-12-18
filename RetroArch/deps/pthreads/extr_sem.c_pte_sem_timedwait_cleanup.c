#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* resultPtr; TYPE_2__* sem; } ;
typedef  TYPE_1__ sem_timedwait_cleanup_args_t ;
typedef  TYPE_2__* sem_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  value; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 scalar_t__ PTE_OS_OK ; 
 scalar_t__ pte_osSemaphorePend (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pte_sem_timedwait_cleanup (void * args)
{
   sem_timedwait_cleanup_args_t * a = (sem_timedwait_cleanup_args_t *)args;
   sem_t s = a->sem;

   if (pthread_mutex_lock (&s->lock) == 0)
   {
      /*
       * We either timed out or were cancelled.
       * If someone has posted between then and now we try to take the semaphore.
       * Otherwise the semaphore count may be wrong after we
       * return. In the case of a cancellation, it is as if we
       * were cancelled just before we return (after taking the semaphore)
       * which is ok.
       */
      unsigned int timeout = 0;
      if (pte_osSemaphorePend(s->sem, &timeout) == PTE_OS_OK)
      {
         /* We got the semaphore on the second attempt */
         *(a->resultPtr) = 0;
      }
      else
      {
         /* Indicate we're no longer waiting */
         s->value++;

         /*
          * Don't release the OS sema, it doesn't need adjustment
          * because it doesn't record the number of waiters.
          */

      }
      (void) pthread_mutex_unlock (&s->lock);
   }
}