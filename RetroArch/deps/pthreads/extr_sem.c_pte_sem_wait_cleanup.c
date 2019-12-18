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
typedef  TYPE_1__* sem_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  value; int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 scalar_t__ PTE_OS_OK ; 
 scalar_t__ pte_osSemaphorePend (int /*<<< orphan*/ ,unsigned int*) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pte_sem_wait_cleanup(void * sem)
{
   sem_t s = (sem_t) sem;
   unsigned int timeout;

   if (pthread_mutex_lock (&s->lock) == 0)
   {
      /*
       * If sema is destroyed do nothing, otherwise:-
       * If the sema is posted between us being cancelled and us locking
       * the sema again above then we need to consume that post but cancel
       * anyway. If we don't get the semaphore we indicate that we're no
       * longer waiting.
       */
      timeout = 0;
      if (pte_osSemaphorePend(s->sem, &timeout) != PTE_OS_OK)
      {
         ++s->value;

         /*
          * Don't release the W32 sema, it doesn't need adjustment
          * because it doesn't record the number of waiters.
          */

      }
      (void) pthread_mutex_unlock (&s->lock);
   }
}