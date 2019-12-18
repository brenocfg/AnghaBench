#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sched_param {int sched_priority; } ;
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_4__ {int /*<<< orphan*/  param; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SCHED_OTHER ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sched_param const*,int) ; 
 scalar_t__ ptw32_is_attr (TYPE_1__**) ; 
 int sched_get_priority_max (int /*<<< orphan*/ ) ; 
 int sched_get_priority_min (int /*<<< orphan*/ ) ; 

int
pthread_attr_setschedparam (pthread_attr_t * attr,
			    const struct sched_param *param)
{
  int priority;

  if (ptw32_is_attr (attr) != 0 || param == NULL)
    {
      return EINVAL;
    }

  priority = param->sched_priority;

  /* Validate priority level. */
  if (priority < sched_get_priority_min (SCHED_OTHER) ||
      priority > sched_get_priority_max (SCHED_OTHER))
    {
      return EINVAL;
    }

  memcpy (&(*attr)->param, param, sizeof (*param));
  return 0;
}