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
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
typedef  scalar_t__ pthread_t ;
struct TYPE_2__ {int /*<<< orphan*/  sched_priority; } ;
typedef  TYPE_1__ pte_thread_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SCHED_MAX ; 
 int SCHED_OTHER ; 
 int pthread_kill (scalar_t__,int /*<<< orphan*/ ) ; 

int pthread_getschedparam (pthread_t thread, int *policy,
      struct sched_param *param)
{
   int result;

   /* Validate the thread id. */
   result = pthread_kill (thread, 0);
   if (0 != result)
      return result;

   /*
    * Validate the policy and param args.
    * Check that a policy constant wasn't passed rather than &policy.
    */
   if (policy <= (int *) SCHED_MAX || param == NULL)
      return EINVAL;

   /* Fill out the policy. */
   *policy = SCHED_OTHER;

   /*
    * This function must return the priority value set by
    * the most recent pthread_setschedparam() or pthread_create()
    * for the target thread. It must not return the actual thread
    * priority as altered by any system priority adjustments etc.
    */
   param->sched_priority = ((pte_thread_t *)thread)->sched_priority;

   return 0;
}