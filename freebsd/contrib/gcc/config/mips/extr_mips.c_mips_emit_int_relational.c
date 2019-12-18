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
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int XOR ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ mips_canonicalize_comparison (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_emit_binary (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mips_relational_operand_ok_p (int,int /*<<< orphan*/ ) ; 
 int reverse_condition (int) ; 

__attribute__((used)) static void
mips_emit_int_relational (enum rtx_code code, bool *invert_ptr,
			  rtx target, rtx cmp0, rtx cmp1)
{
  /* First see if there is a MIPS instruction that can do this operation
     with CMP1 in its current form. If not, try to canonicalize the
     comparison to LT. If that fails, try doing the same for the
     inverse operation.  If that also fails, force CMP1 into a register
     and try again.  */
  if (mips_relational_operand_ok_p (code, cmp1))
    mips_emit_binary (code, target, cmp0, cmp1);
  else if (mips_canonicalize_comparison (&code, &cmp1, GET_MODE (target)))
    mips_emit_binary (code, target, cmp0, cmp1);
  else
    {
      enum rtx_code inv_code = reverse_condition (code);
      if (!mips_relational_operand_ok_p (inv_code, cmp1))
	{
	  cmp1 = force_reg (GET_MODE (cmp0), cmp1);
	  mips_emit_int_relational (code, invert_ptr, target, cmp0, cmp1);
	}
      else if (invert_ptr == 0)
	{
	  rtx inv_target = gen_reg_rtx (GET_MODE (target));
	  mips_emit_binary (inv_code, inv_target, cmp0, cmp1);
	  mips_emit_binary (XOR, target, inv_target, const1_rtx);
	}
      else
	{
	  *invert_ptr = !*invert_ptr;
	  mips_emit_binary (inv_code, target, cmp0, cmp1);
	}
    }
}