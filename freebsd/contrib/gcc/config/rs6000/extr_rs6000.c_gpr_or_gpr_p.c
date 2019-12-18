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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ INT_REGNO_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 

bool
gpr_or_gpr_p (rtx op0, rtx op1)
{
  return ((REG_P (op0) && INT_REGNO_P (REGNO (op0)))
	  || (REG_P (op1) && INT_REGNO_P (REGNO (op1))));
}