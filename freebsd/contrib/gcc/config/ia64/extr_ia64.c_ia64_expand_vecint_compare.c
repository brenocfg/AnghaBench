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
 int /*<<< orphan*/  CONST0_RTX (int) ; 
#define  EQ 140 
#define  GE 139 
 int /*<<< orphan*/  GEN_INT (int) ; 
#define  GEU 138 
#define  GT 137 
#define  GTU 136 
#define  LE 135 
#define  LEU 134 
#define  LT 133 
#define  LTU 132 
#define  NE 131 
#define  V2SImode 130 
#define  V4HImode 129 
#define  V8QImode 128 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_andv2si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int const) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CONST_VECTOR (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_US_MINUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_subv2si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_xorv2si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reverse_condition (int) ; 
 int swap_condition (int) ; 

__attribute__((used)) static bool
ia64_expand_vecint_compare (enum rtx_code code, enum machine_mode mode,
			    rtx dest, rtx op0, rtx op1)
{
  bool negate = false;
  rtx x;

  /* Canonicalize the comparison to EQ, GT, GTU.  */
  switch (code)
    {
    case EQ:
    case GT:
    case GTU:
      break;

    case NE:
    case LE:
    case LEU:
      code = reverse_condition (code);
      negate = true;
      break;

    case GE:
    case GEU:
      code = reverse_condition (code);
      negate = true;
      /* FALLTHRU */

    case LT:
    case LTU:
      code = swap_condition (code);
      x = op0, op0 = op1, op1 = x;
      break;

    default:
      gcc_unreachable ();
    }

  /* Unsigned parallel compare is not supported by the hardware.  Play some
     tricks to turn this into a signed comparison against 0.  */
  if (code == GTU)
    {
      switch (mode)
	{
	case V2SImode:
	  {
	    rtx t1, t2, mask;

	    /* Perform a parallel modulo subtraction.  */
	    t1 = gen_reg_rtx (V2SImode);
	    emit_insn (gen_subv2si3 (t1, op0, op1));

	    /* Extract the original sign bit of op0.  */
	    mask = GEN_INT (-0x80000000);
	    mask = gen_rtx_CONST_VECTOR (V2SImode, gen_rtvec (2, mask, mask));
	    mask = force_reg (V2SImode, mask);
	    t2 = gen_reg_rtx (V2SImode);
	    emit_insn (gen_andv2si3 (t2, op0, mask));

	    /* XOR it back into the result of the subtraction.  This results
	       in the sign bit set iff we saw unsigned underflow.  */
	    x = gen_reg_rtx (V2SImode);
	    emit_insn (gen_xorv2si3 (x, t1, t2));

	    code = GT;
	    op0 = x;
	    op1 = CONST0_RTX (mode);
	  }
	  break;

	case V8QImode:
	case V4HImode:
	  /* Perform a parallel unsigned saturating subtraction.  */
	  x = gen_reg_rtx (mode);
	  emit_insn (gen_rtx_SET (VOIDmode, x,
				  gen_rtx_US_MINUS (mode, op0, op1)));

	  code = EQ;
	  op0 = x;
	  op1 = CONST0_RTX (mode);
	  negate = !negate;
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  x = gen_rtx_fmt_ee (code, mode, op0, op1);
  emit_insn (gen_rtx_SET (VOIDmode, dest, x));

  return negate;
}