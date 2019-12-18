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

/* Variables and functions */
 int EQ ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_INT ; 
 int NE ; 
 int /*<<< orphan*/ * cmp_operands ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_emit_binary (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_emit_int_relational (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_zero_if_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
mips_emit_scc (enum rtx_code code, rtx target)
{
  if (GET_MODE_CLASS (GET_MODE (cmp_operands[0])) != MODE_INT)
    return false;

  target = gen_lowpart (GET_MODE (cmp_operands[0]), target);
  if (code == EQ || code == NE)
    {
      rtx zie = mips_zero_if_equal (cmp_operands[0], cmp_operands[1]);
      mips_emit_binary (code, target, zie, const0_rtx);
    }
  else
    mips_emit_int_relational (code, 0, target,
			      cmp_operands[0], cmp_operands[1]);
  return true;
}