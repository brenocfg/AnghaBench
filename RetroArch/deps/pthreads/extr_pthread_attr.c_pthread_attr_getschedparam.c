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
struct sched_param {int dummy; } ;
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_4__ {int /*<<< orphan*/  param; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct sched_param*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ pte_is_attr (TYPE_1__* const*) ; 

int pthread_attr_getschedparam (const pthread_attr_t * attr,
      struct sched_param *param)
{
   if (pte_is_attr (attr) != 0 || param == NULL)
      return EINVAL;

   memcpy (param, &(*attr)->param, sizeof (*param));
   return 0;
}