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
 int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/ * regno_reg_rtx ; 
 int /*<<< orphan*/  use_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
use_regs (rtx *call_fusage, int regno, int nregs)
{
  int i;

  gcc_assert (regno + nregs <= FIRST_PSEUDO_REGISTER);

  for (i = 0; i < nregs; i++)
    use_reg (call_fusage, regno_reg_rtx[regno + i]);
}