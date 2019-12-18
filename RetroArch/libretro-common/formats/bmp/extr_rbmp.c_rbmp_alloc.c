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
typedef  int /*<<< orphan*/  rbmp_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

rbmp_t *rbmp_alloc(void)
{
   rbmp_t *rbmp = (rbmp_t*)calloc(1, sizeof(*rbmp));
   if (!rbmp)
      return NULL;
   return rbmp;
}