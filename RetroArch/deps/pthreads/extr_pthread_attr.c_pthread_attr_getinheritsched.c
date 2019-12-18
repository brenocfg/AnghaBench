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
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_4__ {int inheritsched; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ pte_is_attr (TYPE_1__**) ; 

int pthread_attr_getinheritsched (pthread_attr_t * attr, int *inheritsched)
{
   if (pte_is_attr (attr) != 0 || inheritsched == NULL)
      return EINVAL;

   *inheritsched = (*attr)->inheritsched;
   return 0;
}