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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int n_earlyclobbers ; 
 scalar_t__* reload_earlyclobbers ; 

int
earlyclobber_operand_p (rtx x)
{
  int i;

  for (i = 0; i < n_earlyclobbers; i++)
    if (reload_earlyclobbers[i] == x)
      return 1;

  return 0;
}