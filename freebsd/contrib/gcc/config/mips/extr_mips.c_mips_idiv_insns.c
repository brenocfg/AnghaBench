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
 scalar_t__ GENERATE_DIVIDE_TRAPS ; 
 scalar_t__ TARGET_CHECK_ZERO_DIV ; 
 scalar_t__ TARGET_FIX_R4000 ; 
 scalar_t__ TARGET_FIX_R4400 ; 

int
mips_idiv_insns (void)
{
  int count;

  count = 1;
  if (TARGET_CHECK_ZERO_DIV)
    {
      if (GENERATE_DIVIDE_TRAPS)
        count++;
      else
        count += 2;
    }

  if (TARGET_FIX_R4000 || TARGET_FIX_R4400)
    count++;
  return count;
}