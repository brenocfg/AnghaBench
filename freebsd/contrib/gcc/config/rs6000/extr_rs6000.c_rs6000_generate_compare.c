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
 int CCEQmode ; 
 int CCFPmode ; 
 int CCUNSmode ; 
 int CCmode ; 
#define  DFmode 145 
#define  EQ 144 
#define  GE 143 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
#define  GEU 142 
#define  GT 141 
#define  GTU 140 
#define  LE 139 
#define  LEU 138 
#define  LT 137 
#define  LTGT 136 
#define  LTU 135 
#define  NE 134 
#define  SFmode 133 
 int SImode ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_PROMOTED_UNSIGNED_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_E500 ; 
 scalar_t__ TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 int /*<<< orphan*/  TARGET_IEEEQUAD ; 
 scalar_t__ TARGET_LONG_DOUBLE_128 ; 
 scalar_t__ TARGET_XL_COMPAT ; 
 int TFmode ; 
#define  UNEQ 132 
#define  UNGE 131 
#define  UNGT 130 
#define  UNLE 129 
#define  UNLT 128 
 int UNORDERED ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_SP_TEST ; 
 int VOIDmode ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const_true_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_finite_math_only ; 
 int /*<<< orphan*/  flag_unsafe_math_optimizations ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_cmpdfeq_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpdfgt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpdflt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpsfeq_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpsfgt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpsflt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_e500_cr_ior_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_COMPARE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_IOR (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SCRATCH (int const) ; 
 int /*<<< orphan*/  gen_rtx_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_stack_protect_testdi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_stack_protect_testsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tstdfeq_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tstdfgt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tstdflt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tstsfeq_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tstsfgt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tstsflt_gpr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rs6000_compare_fp_p ; 
 int /*<<< orphan*/  rs6000_compare_op0 ; 
 int /*<<< orphan*/  rs6000_compare_op1 ; 
 int /*<<< orphan*/  validate_condition_mode (int,int) ; 

__attribute__((used)) static rtx
rs6000_generate_compare (enum rtx_code code)
{
  enum machine_mode comp_mode;
  rtx compare_result;

  if (rs6000_compare_fp_p)
    comp_mode = CCFPmode;
  else if (code == GTU || code == LTU
	   || code == GEU || code == LEU)
    comp_mode = CCUNSmode;
  else if ((code == EQ || code == NE)
	   && GET_CODE (rs6000_compare_op0) == SUBREG
	   && GET_CODE (rs6000_compare_op1) == SUBREG
	   && SUBREG_PROMOTED_UNSIGNED_P (rs6000_compare_op0)
	   && SUBREG_PROMOTED_UNSIGNED_P (rs6000_compare_op1))
    /* These are unsigned values, perhaps there will be a later
       ordering compare that can be shared with this one.
       Unfortunately we cannot detect the signedness of the operands
       for non-subregs.  */
    comp_mode = CCUNSmode;
  else
    comp_mode = CCmode;

  /* First, the compare.  */
  compare_result = gen_reg_rtx (comp_mode);

  /* E500 FP compare instructions on the GPRs.  Yuck!  */
  if ((TARGET_E500 && !TARGET_FPRS && TARGET_HARD_FLOAT)
      && rs6000_compare_fp_p)
    {
      rtx cmp, or_result, compare_result2;
      enum machine_mode op_mode = GET_MODE (rs6000_compare_op0);

      if (op_mode == VOIDmode)
	op_mode = GET_MODE (rs6000_compare_op1);

      /* The E500 FP compare instructions toggle the GT bit (CR bit 1) only.
	 This explains the following mess.  */

      switch (code)
	{
	case EQ: case UNEQ: case NE: case LTGT:
	  switch (op_mode)
	    {
	    case SFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstsfeq_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpsfeq_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    case DFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstdfeq_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpdfeq_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    default:
	      gcc_unreachable ();
	    }
	  break;

	case GT: case GTU: case UNGT: case UNGE: case GE: case GEU:
	  switch (op_mode)
	    {
	    case SFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstsfgt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpsfgt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    case DFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstdfgt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpdfgt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    default:
	      gcc_unreachable ();
	    }
	  break;

	case LT: case LTU: case UNLT: case UNLE: case LE: case LEU:
	  switch (op_mode)
	    {
	    case SFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstsflt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpsflt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    case DFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstdflt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpdflt_gpr (compare_result, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    default:
	      gcc_unreachable ();
	    }
	  break;
        default:
          gcc_unreachable ();
	}

      /* Synthesize LE and GE from LT/GT || EQ.  */
      if (code == LE || code == GE || code == LEU || code == GEU)
	{
	  emit_insn (cmp);

	  switch (code)
	    {
	    case LE: code = LT; break;
	    case GE: code = GT; break;
	    case LEU: code = LT; break;
	    case GEU: code = GT; break;
	    default: gcc_unreachable ();
	    }

	  compare_result2 = gen_reg_rtx (CCFPmode);

	  /* Do the EQ.  */
	  switch (op_mode)
	    {
	    case SFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstsfeq_gpr (compare_result2, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpsfeq_gpr (compare_result2, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    case DFmode:
	      cmp = flag_unsafe_math_optimizations
		? gen_tstdfeq_gpr (compare_result2, rs6000_compare_op0,
				   rs6000_compare_op1)
		: gen_cmpdfeq_gpr (compare_result2, rs6000_compare_op0,
				   rs6000_compare_op1);
	      break;

	    default:
	      gcc_unreachable ();
	    }
	  emit_insn (cmp);

	  /* OR them together.  */
	  or_result = gen_reg_rtx (CCFPmode);
	  cmp = gen_e500_cr_ior_compare (or_result, compare_result,
					   compare_result2);
	  compare_result = or_result;
	  code = EQ;
	}
      else
	{
	  if (code == NE || code == LTGT)
	    code = NE;
	  else
	    code = EQ;
	}

      emit_insn (cmp);
    }
  else
    {
      /* Generate XLC-compatible TFmode compare as PARALLEL with extra
	 CLOBBERs to match cmptf_internal2 pattern.  */
      if (comp_mode == CCFPmode && TARGET_XL_COMPAT
	  && GET_MODE (rs6000_compare_op0) == TFmode
	  && !TARGET_IEEEQUAD
	  && TARGET_HARD_FLOAT && TARGET_FPRS && TARGET_LONG_DOUBLE_128)
	emit_insn (gen_rtx_PARALLEL (VOIDmode,
	  gen_rtvec (9,
		     gen_rtx_SET (VOIDmode,
				  compare_result,
				  gen_rtx_COMPARE (comp_mode,
						   rs6000_compare_op0,
						   rs6000_compare_op1)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)),
		     gen_rtx_CLOBBER (VOIDmode, gen_rtx_SCRATCH (DFmode)))));
      else if (GET_CODE (rs6000_compare_op1) == UNSPEC
	       && XINT (rs6000_compare_op1, 1) == UNSPEC_SP_TEST)
	{
	  rtx op1 = XVECEXP (rs6000_compare_op1, 0, 0);
	  comp_mode = CCEQmode;
	  compare_result = gen_reg_rtx (CCEQmode);
	  if (TARGET_64BIT)
	    emit_insn (gen_stack_protect_testdi (compare_result,
						 rs6000_compare_op0, op1));
	  else
	    emit_insn (gen_stack_protect_testsi (compare_result,
						 rs6000_compare_op0, op1));
	}
      else
	emit_insn (gen_rtx_SET (VOIDmode, compare_result,
				gen_rtx_COMPARE (comp_mode,
						 rs6000_compare_op0,
						 rs6000_compare_op1)));
    }

  /* Some kinds of FP comparisons need an OR operation;
     under flag_finite_math_only we don't bother.  */
  if (rs6000_compare_fp_p
      && !flag_finite_math_only
      && !(TARGET_HARD_FLOAT && TARGET_E500 && !TARGET_FPRS)
      && (code == LE || code == GE
	  || code == UNEQ || code == LTGT
	  || code == UNGT || code == UNLT))
    {
      enum rtx_code or1, or2;
      rtx or1_rtx, or2_rtx, compare2_rtx;
      rtx or_result = gen_reg_rtx (CCEQmode);

      switch (code)
	{
	case LE: or1 = LT;  or2 = EQ;  break;
	case GE: or1 = GT;  or2 = EQ;  break;
	case UNEQ: or1 = UNORDERED;  or2 = EQ;  break;
	case LTGT: or1 = LT;  or2 = GT;  break;
	case UNGT: or1 = UNORDERED;  or2 = GT;  break;
	case UNLT: or1 = UNORDERED;  or2 = LT;  break;
	default:  gcc_unreachable ();
	}
      validate_condition_mode (or1, comp_mode);
      validate_condition_mode (or2, comp_mode);
      or1_rtx = gen_rtx_fmt_ee (or1, SImode, compare_result, const0_rtx);
      or2_rtx = gen_rtx_fmt_ee (or2, SImode, compare_result, const0_rtx);
      compare2_rtx = gen_rtx_COMPARE (CCEQmode,
				      gen_rtx_IOR (SImode, or1_rtx, or2_rtx),
				      const_true_rtx);
      emit_insn (gen_rtx_SET (VOIDmode, or_result, compare2_rtx));

      compare_result = or_result;
      code = EQ;
    }

  validate_condition_mode (code, GET_MODE (compare_result));

  return gen_rtx_fmt_ee (code, VOIDmode, compare_result, const0_rtx);
}