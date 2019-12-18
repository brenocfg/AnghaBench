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
 scalar_t__ CCmode ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SImode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_isel_signed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_isel_unsigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs6000_compare_op0 ; 
 int /*<<< orphan*/  rs6000_generate_compare (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rs6000_emit_int_cmove (rtx dest, rtx op, rtx true_cond, rtx false_cond)
{
  rtx condition_rtx, cr;

  /* All isel implementations thus far are 32-bits.  */
  if (GET_MODE (rs6000_compare_op0) != SImode)
    return 0;

  /* We still have to do the compare, because isel doesn't do a
     compare, it just looks at the CRx bits set by a previous compare
     instruction.  */
  condition_rtx = rs6000_generate_compare (GET_CODE (op));
  cr = XEXP (condition_rtx, 0);

  if (GET_MODE (cr) == CCmode)
    emit_insn (gen_isel_signed (dest, condition_rtx,
				true_cond, false_cond, cr));
  else
    emit_insn (gen_isel_unsigned (dest, condition_rtx,
				  true_cond, false_cond, cr));

  return 1;
}