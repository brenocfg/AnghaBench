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
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int CCNOmode ; 
 int CCmode ; 
#define  EQ 141 
 int /*<<< orphan*/  FLAGS_REG ; 
#define  GE 140 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GEU ; 
#define  GT 139 
 int /*<<< orphan*/  HImode ; 
#define  LE 138 
#define  LT 137 
#define  LTGT 136 
 int LTU ; 
#define  NE 135 
 scalar_t__ NULL_RTX ; 
#define  ORDERED 134 
 scalar_t__ TARGET_CMOVE ; 
 int /*<<< orphan*/  TARGET_IEEE_FP ; 
#define  UNEQ 133 
#define  UNGE 132 
#define  UNGT 131 
 int UNKNOWN ; 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 int /*<<< orphan*/  UNSPEC_FNSTSW ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  constm1_rtx ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_addqi_ext_1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_andqi_ext_0 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_cmpqi_ext_3 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__) ; 
 scalar_t__ gen_rtx_COMPARE (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_REG (int,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_testqi_ext_ccno_0 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_x86_sahf_1 (scalar_t__) ; 
 scalar_t__ gen_xorqi_cc_ext_1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int ix86_fp_compare_mode (int) ; 
 int ix86_fp_comparison_arithmetics_cost (int) ; 
 int /*<<< orphan*/  ix86_fp_comparison_codes (int,int*,int*,int*) ; 
 int ix86_fp_comparison_cost (int) ; 
 int ix86_prepare_fp_compare_args (int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static rtx
ix86_expand_fp_compare (enum rtx_code code, rtx op0, rtx op1, rtx scratch,
			rtx *second_test, rtx *bypass_test)
{
  enum machine_mode fpcmp_mode, intcmp_mode;
  rtx tmp, tmp2;
  int cost = ix86_fp_comparison_cost (code);
  enum rtx_code bypass_code, first_code, second_code;

  fpcmp_mode = ix86_fp_compare_mode (code);
  code = ix86_prepare_fp_compare_args (code, &op0, &op1);

  if (second_test)
    *second_test = NULL_RTX;
  if (bypass_test)
    *bypass_test = NULL_RTX;

  ix86_fp_comparison_codes (code, &bypass_code, &first_code, &second_code);

  /* Do fcomi/sahf based test when profitable.  */
  if ((bypass_code == UNKNOWN || bypass_test)
      && (second_code == UNKNOWN || second_test)
      && ix86_fp_comparison_arithmetics_cost (code) > cost)
    {
      if (TARGET_CMOVE)
	{
	  tmp = gen_rtx_COMPARE (fpcmp_mode, op0, op1);
	  tmp = gen_rtx_SET (VOIDmode, gen_rtx_REG (fpcmp_mode, FLAGS_REG),
			     tmp);
	  emit_insn (tmp);
	}
      else
	{
	  tmp = gen_rtx_COMPARE (fpcmp_mode, op0, op1);
	  tmp2 = gen_rtx_UNSPEC (HImode, gen_rtvec (1, tmp), UNSPEC_FNSTSW);
	  if (!scratch)
	    scratch = gen_reg_rtx (HImode);
	  emit_insn (gen_rtx_SET (VOIDmode, scratch, tmp2));
	  emit_insn (gen_x86_sahf_1 (scratch));
	}

      /* The FP codes work out to act like unsigned.  */
      intcmp_mode = fpcmp_mode;
      code = first_code;
      if (bypass_code != UNKNOWN)
	*bypass_test = gen_rtx_fmt_ee (bypass_code, VOIDmode,
				       gen_rtx_REG (intcmp_mode, FLAGS_REG),
				       const0_rtx);
      if (second_code != UNKNOWN)
	*second_test = gen_rtx_fmt_ee (second_code, VOIDmode,
				       gen_rtx_REG (intcmp_mode, FLAGS_REG),
				       const0_rtx);
    }
  else
    {
      /* Sadness wrt reg-stack pops killing fpsr -- gotta get fnstsw first.  */
      tmp = gen_rtx_COMPARE (fpcmp_mode, op0, op1);
      tmp2 = gen_rtx_UNSPEC (HImode, gen_rtvec (1, tmp), UNSPEC_FNSTSW);
      if (!scratch)
	scratch = gen_reg_rtx (HImode);
      emit_insn (gen_rtx_SET (VOIDmode, scratch, tmp2));

      /* In the unordered case, we have to check C2 for NaN's, which
	 doesn't happen to work out to anything nice combination-wise.
	 So do some bit twiddling on the value we've got in AH to come
	 up with an appropriate set of condition codes.  */

      intcmp_mode = CCNOmode;
      switch (code)
	{
	case GT:
	case UNGT:
	  if (code == GT || !TARGET_IEEE_FP)
	    {
	      emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x45)));
	      code = EQ;
	    }
	  else
	    {
	      emit_insn (gen_andqi_ext_0 (scratch, scratch, GEN_INT (0x45)));
	      emit_insn (gen_addqi_ext_1 (scratch, scratch, constm1_rtx));
	      emit_insn (gen_cmpqi_ext_3 (scratch, GEN_INT (0x44)));
	      intcmp_mode = CCmode;
	      code = GEU;
	    }
	  break;
	case LT:
	case UNLT:
	  if (code == LT && TARGET_IEEE_FP)
	    {
	      emit_insn (gen_andqi_ext_0 (scratch, scratch, GEN_INT (0x45)));
	      emit_insn (gen_cmpqi_ext_3 (scratch, GEN_INT (0x01)));
	      intcmp_mode = CCmode;
	      code = EQ;
	    }
	  else
	    {
	      emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x01)));
	      code = NE;
	    }
	  break;
	case GE:
	case UNGE:
	  if (code == GE || !TARGET_IEEE_FP)
	    {
	      emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x05)));
	      code = EQ;
	    }
	  else
	    {
	      emit_insn (gen_andqi_ext_0 (scratch, scratch, GEN_INT (0x45)));
	      emit_insn (gen_xorqi_cc_ext_1 (scratch, scratch,
					     GEN_INT (0x01)));
	      code = NE;
	    }
	  break;
	case LE:
	case UNLE:
	  if (code == LE && TARGET_IEEE_FP)
	    {
	      emit_insn (gen_andqi_ext_0 (scratch, scratch, GEN_INT (0x45)));
	      emit_insn (gen_addqi_ext_1 (scratch, scratch, constm1_rtx));
	      emit_insn (gen_cmpqi_ext_3 (scratch, GEN_INT (0x40)));
	      intcmp_mode = CCmode;
	      code = LTU;
	    }
	  else
	    {
	      emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x45)));
	      code = NE;
	    }
	  break;
	case EQ:
	case UNEQ:
	  if (code == EQ && TARGET_IEEE_FP)
	    {
	      emit_insn (gen_andqi_ext_0 (scratch, scratch, GEN_INT (0x45)));
	      emit_insn (gen_cmpqi_ext_3 (scratch, GEN_INT (0x40)));
	      intcmp_mode = CCmode;
	      code = EQ;
	    }
	  else
	    {
	      emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x40)));
	      code = NE;
	      break;
	    }
	  break;
	case NE:
	case LTGT:
	  if (code == NE && TARGET_IEEE_FP)
	    {
	      emit_insn (gen_andqi_ext_0 (scratch, scratch, GEN_INT (0x45)));
	      emit_insn (gen_xorqi_cc_ext_1 (scratch, scratch,
					     GEN_INT (0x40)));
	      code = NE;
	    }
	  else
	    {
	      emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x40)));
	      code = EQ;
	    }
	  break;

	case UNORDERED:
	  emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x04)));
	  code = NE;
	  break;
	case ORDERED:
	  emit_insn (gen_testqi_ext_ccno_0 (scratch, GEN_INT (0x04)));
	  code = EQ;
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  /* Return the test that should be put into the flags user, i.e.
     the bcc, scc, or cmov instruction.  */
  return gen_rtx_fmt_ee (code, VOIDmode,
			 gen_rtx_REG (intcmp_mode, FLAGS_REG),
			 const0_rtx);
}