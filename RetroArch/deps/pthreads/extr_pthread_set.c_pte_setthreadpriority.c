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
struct TYPE_2__ {int sched_priority; int /*<<< orphan*/  threadLock; int /*<<< orphan*/  threadId; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ pte_osThreadSetPriority (int /*<<< orphan*/ ,int) ; 
 int pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int sched_get_priority_max (int) ; 
 int sched_get_priority_min (int) ; 

int
pte_setthreadpriority (pthread_t thread, int policy, int priority)
{
   int prio;
   int result;
   pte_thread_t * tp = (pte_thread_t *) thread;

   prio = priority;

   /* Validate priority level. */
   if (prio < sched_get_priority_min (policy) ||
         prio > sched_get_priority_max (policy))
      return EINVAL;

   result = pthread_mutex_lock (&tp->threadLock);

   if (0 == result)
   {
      /* If this fails, the current priority is unchanged. */

      if (0 != pte_osThreadSetPriority(tp->threadId, prio))
         result = EINVAL;
      else
      {
         /*
          * Must record the thread's sched_priority as given,
          * not as finally adjusted.
          */
         tp->sched_priority = priority;
      }

      (void) pthread_mutex_unlock (&tp->threadLock);
   }

   return result;
}