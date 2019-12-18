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
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
use_reg (rtx *call_fusage, rtx reg)
{
  gcc_assert (REG_P (reg) && REGNO (reg) < FIRST_PSEUDO_REGISTER);

  *call_fusage
    = gen_rtx_EXPR_LIST (VOIDmode,
			 gen_rtx_USE (VOIDmode, reg), *call_fusage);
}