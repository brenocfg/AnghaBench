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
 scalar_t__ BImode ; 
 int /*<<< orphan*/  DImode ; 
#define  EQ 135 
#define  GE 134 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
#define  GT 133 
 int /*<<< orphan*/  LCT_CONST ; 
#define  LE 132 
#define  LT 131 
#define  NE 130 
#define  ORDERED 129 
 scalar_t__ TFmode ; 
#define  UNORDERED 128 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ cmptf_libfunc ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_libcall_block (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ emit_library_call_value (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_reg_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_fmt_ee (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ get_insns () ; 
 scalar_t__ ia64_compare_op0 ; 
 scalar_t__ ia64_compare_op1 ; 
 int /*<<< orphan*/  start_sequence () ; 

rtx
ia64_expand_compare (enum rtx_code code, enum machine_mode mode)
{
  rtx op0 = ia64_compare_op0, op1 = ia64_compare_op1;
  rtx cmp;

  /* If we have a BImode input, then we already have a compare result, and
     do not need to emit another comparison.  */
  if (GET_MODE (op0) == BImode)
    {
      gcc_assert ((code == NE || code == EQ) && op1 == const0_rtx);
      cmp = op0;
    }
  /* HPUX TFmode compare requires a library call to _U_Qfcmp, which takes a
     magic number as its third argument, that indicates what to do.
     The return value is an integer to be compared against zero.  */
  else if (GET_MODE (op0) == TFmode)
    {
      enum qfcmp_magic {
	QCMP_INV = 1,	/* Raise FP_INVALID on SNaN as a side effect.  */
	QCMP_UNORD = 2,
	QCMP_EQ = 4,
	QCMP_LT = 8,
	QCMP_GT = 16
      } magic;
      enum rtx_code ncode;
      rtx ret, insns;
      
      gcc_assert (cmptf_libfunc && GET_MODE (op1) == TFmode);
      switch (code)
	{
	  /* 1 = equal, 0 = not equal.  Equality operators do
	     not raise FP_INVALID when given an SNaN operand.  */
	case EQ:        magic = QCMP_EQ;                  ncode = NE; break;
	case NE:        magic = QCMP_EQ;                  ncode = EQ; break;
	  /* isunordered() from C99.  */
	case UNORDERED: magic = QCMP_UNORD;               ncode = NE; break;
	case ORDERED:   magic = QCMP_UNORD;               ncode = EQ; break;
	  /* Relational operators raise FP_INVALID when given
	     an SNaN operand.  */
	case LT:        magic = QCMP_LT        |QCMP_INV; ncode = NE; break;
	case LE:        magic = QCMP_LT|QCMP_EQ|QCMP_INV; ncode = NE; break;
	case GT:        magic = QCMP_GT        |QCMP_INV; ncode = NE; break;
	case GE:        magic = QCMP_GT|QCMP_EQ|QCMP_INV; ncode = NE; break;
	  /* FUTURE: Implement UNEQ, UNLT, UNLE, UNGT, UNGE, LTGT.
	     Expanders for buneq etc. weuld have to be added to ia64.md
	     for this to be useful.  */
	default: gcc_unreachable ();
	}

      start_sequence ();

      ret = emit_library_call_value (cmptf_libfunc, 0, LCT_CONST, DImode, 3,
				     op0, TFmode, op1, TFmode,
				     GEN_INT (magic), DImode);
      cmp = gen_reg_rtx (BImode);
      emit_insn (gen_rtx_SET (VOIDmode, cmp,
			      gen_rtx_fmt_ee (ncode, BImode,
					      ret, const0_rtx)));

      insns = get_insns ();
      end_sequence ();

      emit_libcall_block (insns, cmp, cmp,
			  gen_rtx_fmt_ee (code, BImode, op0, op1));
      code = NE;
    }
  else
    {
      cmp = gen_reg_rtx (BImode);
      emit_insn (gen_rtx_SET (VOIDmode, cmp,
			      gen_rtx_fmt_ee (code, BImode, op0, op1)));
      code = NE;
    }

  return gen_rtx_fmt_ee (code, mode, cmp, const0_rtx);
}