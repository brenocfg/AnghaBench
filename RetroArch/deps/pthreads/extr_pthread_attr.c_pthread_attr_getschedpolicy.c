#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SCHED_MAX ; 
 int SCHED_OTHER ; 
 scalar_t__ pte_is_attr (int /*<<< orphan*/ *) ; 

int pthread_attr_getschedpolicy (pthread_attr_t * attr, int *policy)
{
   if (pte_is_attr (attr) != 0 || policy == NULL)
      return EINVAL;

   /*
    * Validate the policy arg.
    * Check that a policy constant wasn't passed rather than &policy.
    */
   if (policy <= (int *) SCHED_MAX)
      return EINVAL;

   *policy = SCHED_OTHER;

   return 0;
}