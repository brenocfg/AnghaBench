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
typedef  int /*<<< orphan*/  rtvec ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  ABS ; 
 int /*<<< orphan*/  CONST0_RTX (int) ; 
 scalar_t__ CONST_DOUBLE ; 
 int /*<<< orphan*/  CONST_DOUBLE_REAL_VALUE (int /*<<< orphan*/ ) ; 
 int DFmode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int SFmode ; 
 int V2DFmode ; 
 int V4SFmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_copysigndf3_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_copysigndf3_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_copysignsf3_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_copysignsf3_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gen_rtx_CONST_VECTOR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_build_signbit_mask (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ real_isneg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_unary_operation (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

void
ix86_expand_copysign (rtx operands[])
{
  enum machine_mode mode, vmode;
  rtx dest, op0, op1, mask, nmask;

  dest = operands[0];
  op0 = operands[1];
  op1 = operands[2];

  mode = GET_MODE (dest);
  vmode = mode == SFmode ? V4SFmode : V2DFmode;

  if (GET_CODE (op0) == CONST_DOUBLE)
    {
      rtvec v;

      if (real_isneg (CONST_DOUBLE_REAL_VALUE (op0)))
	op0 = simplify_unary_operation (ABS, mode, op0, mode);

      if (op0 == CONST0_RTX (mode))
	op0 = CONST0_RTX (vmode);
      else
        {
	  if (mode == SFmode)
	    v = gen_rtvec (4, op0, CONST0_RTX (SFmode),
                           CONST0_RTX (SFmode), CONST0_RTX (SFmode));
	  else
	    v = gen_rtvec (2, op0, CONST0_RTX (DFmode));
          op0 = force_reg (vmode, gen_rtx_CONST_VECTOR (vmode, v));
	}

      mask = ix86_build_signbit_mask (mode, 0, 0);

      if (mode == SFmode)
	emit_insn (gen_copysignsf3_const (dest, op0, op1, mask));
      else
	emit_insn (gen_copysigndf3_const (dest, op0, op1, mask));
    }
  else
    {
      nmask = ix86_build_signbit_mask (mode, 0, 1);
      mask = ix86_build_signbit_mask (mode, 0, 0);

      if (mode == SFmode)
	emit_insn (gen_copysignsf3_var (dest, NULL, op0, op1, nmask, mask));
      else
	emit_insn (gen_copysigndf3_var (dest, NULL, op0, op1, nmask, mask));
    }
}