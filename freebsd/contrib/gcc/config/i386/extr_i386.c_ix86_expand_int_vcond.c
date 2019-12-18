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
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
#define  GEU 138 
#define  GT 137 
#define  GTU 136 
#define  LE 135 
#define  LEU 134 
#define  LT 133 
#define  LTU 132 
#define  NE 131 
#define  V16QImode 130 
#define  V4SImode 129 
#define  V8HImode 128 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_andv4si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CONST_VECTOR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_US_MINUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_subv4si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_xorv4si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_expand_sse_cmp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_expand_sse_movcc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reverse_condition (int) ; 
 int swap_condition (int) ; 

bool
ix86_expand_int_vcond (rtx operands[])
{
  enum machine_mode mode = GET_MODE (operands[0]);
  enum rtx_code code = GET_CODE (operands[3]);
  bool negate = false;
  rtx x, cop0, cop1;

  cop0 = operands[4];
  cop1 = operands[5];

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
      x = cop0, cop0 = cop1, cop1 = x;
      break;

    default:
      gcc_unreachable ();
    }

  /* Unsigned parallel compare is not supported by the hardware.  Play some
     tricks to turn this into a signed comparison against 0.  */
  if (code == GTU)
    {
      cop0 = force_reg (mode, cop0);

      switch (mode)
	{
	case V4SImode:
	  {
	    rtx t1, t2, mask;

	    /* Perform a parallel modulo subtraction.  */
	    t1 = gen_reg_rtx (mode);
	    emit_insn (gen_subv4si3 (t1, cop0, cop1));

	    /* Extract the original sign bit of op0.  */
	    mask = GEN_INT (-0x80000000);
	    mask = gen_rtx_CONST_VECTOR (mode,
			gen_rtvec (4, mask, mask, mask, mask));
	    mask = force_reg (mode, mask);
	    t2 = gen_reg_rtx (mode);
	    emit_insn (gen_andv4si3 (t2, cop0, mask));

	    /* XOR it back into the result of the subtraction.  This results
	       in the sign bit set iff we saw unsigned underflow.  */
	    x = gen_reg_rtx (mode);
	    emit_insn (gen_xorv4si3 (x, t1, t2));

	    code = GT;
	  }
	  break;

	case V16QImode:
	case V8HImode:
	  /* Perform a parallel unsigned saturating subtraction.  */
	  x = gen_reg_rtx (mode);
	  emit_insn (gen_rtx_SET (VOIDmode, x,
				  gen_rtx_US_MINUS (mode, cop0, cop1)));

	  code = EQ;
	  negate = !negate;
	  break;

	default:
	  gcc_unreachable ();
	}

      cop0 = x;
      cop1 = CONST0_RTX (mode);
    }

  x = ix86_expand_sse_cmp (operands[0], code, cop0, cop1,
			   operands[1+negate], operands[2-negate]);

  ix86_expand_sse_movcc (operands[0], x, operands[1+negate],
			 operands[2-negate]);
  return true;
}