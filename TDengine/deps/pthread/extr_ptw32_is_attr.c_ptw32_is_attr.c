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
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_3__ {scalar_t__ valid; } ;

/* Variables and functions */
 scalar_t__ PTW32_ATTR_VALID ; 

int
ptw32_is_attr (const pthread_attr_t * attr)
{
  /* Return 0 if the attr object is valid, non-zero otherwise. */

  return (attr == NULL ||
	  *attr == NULL || (*attr)->valid != PTW32_ATTR_VALID);
}