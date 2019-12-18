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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CC_REGNUM ; 
 int SELECT_CC_MODE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_set_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_COMPARE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,int /*<<< orphan*/ ) ; 

rtx
arm_gen_compare_reg (enum rtx_code code, rtx x, rtx y)
{
  enum machine_mode mode = SELECT_CC_MODE (code, x, y);
  rtx cc_reg = gen_rtx_REG (mode, CC_REGNUM);

  emit_set_insn (cc_reg, gen_rtx_COMPARE (mode, x, y));

  return cc_reg;
}