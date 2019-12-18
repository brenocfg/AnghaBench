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
 size_t REGNO (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 

__attribute__((used)) static bool
store_ops_ok (rtx x, int *regs_set)
{
  rtx reg;

  for (; x; x = XEXP (x, 1))
    {
      reg = XEXP (x, 0);
      if (regs_set[REGNO(reg)])
	return false;
    }

  return true;
}