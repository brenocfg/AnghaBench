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
 scalar_t__* global_regs ; 

__attribute__((used)) static bool
no_global_regs_above (int first_greg)
{
  int i;
  for (i = 0; i < 32 - first_greg; i++)
    if (global_regs[first_greg + i])
      return false;
  return true;
}