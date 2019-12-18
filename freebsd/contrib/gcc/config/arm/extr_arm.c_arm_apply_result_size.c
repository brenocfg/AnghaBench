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

/* Variables and functions */
 scalar_t__ TARGET_ARM ; 
 scalar_t__ TARGET_FPA ; 
 scalar_t__ TARGET_HARD_FLOAT_ABI ; 
 scalar_t__ TARGET_IWMMXT_ABI ; 
 scalar_t__ TARGET_MAVERICK ; 

int
arm_apply_result_size (void)
{
  int size = 16;

  if (TARGET_ARM)
    {
      if (TARGET_HARD_FLOAT_ABI)
	{
	  if (TARGET_FPA)
	    size += 12;
	  if (TARGET_MAVERICK)
	    size += 8;
	}
      if (TARGET_IWMMXT_ABI)
	size += 8;
    }

  return size;
}