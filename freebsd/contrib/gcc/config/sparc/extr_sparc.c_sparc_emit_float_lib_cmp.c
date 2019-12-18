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
 int DImode ; 
#define  EQ 141 
#define  GE 140 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
#define  GT 139 
 int /*<<< orphan*/  LCT_NORMAL ; 
#define  LE 138 
#define  LT 137 
#define  LTGT 136 
 scalar_t__ MEM ; 
#define  NE 135 
 int /*<<< orphan*/  NULL_RTX ; 
#define  ORDERED 134 
 int /*<<< orphan*/  Pmode ; 
 int SImode ; 
 int /*<<< orphan*/  TARGET_ARCH32 ; 
 scalar_t__ TARGET_ARCH64 ; 
 int /*<<< orphan*/  TFmode ; 
#define  UNEQ 133 
#define  UNGE 132 
#define  UNGT 131 
#define  UNLE 130 
#define  UNLT 129 
#define  UNORDERED 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_stack_temp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  const2_rtx ; 
 int /*<<< orphan*/  emit_cmp_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_anddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_andsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  hard_libcall_value (int) ; 

void
sparc_emit_float_lib_cmp (rtx x, rtx y, enum rtx_code comparison)
{
  const char *qpfunc;
  rtx slot0, slot1, result, tem, tem2;
  enum machine_mode mode;

  switch (comparison)
    {
    case EQ:
      qpfunc = (TARGET_ARCH64) ? "_Qp_feq" : "_Q_feq";
      break;

    case NE:
      qpfunc = (TARGET_ARCH64) ? "_Qp_fne" : "_Q_fne";
      break;

    case GT:
      qpfunc = (TARGET_ARCH64) ? "_Qp_fgt" : "_Q_fgt";
      break;

    case GE:
      qpfunc = (TARGET_ARCH64) ? "_Qp_fge" : "_Q_fge";
      break;

    case LT:
      qpfunc = (TARGET_ARCH64) ? "_Qp_flt" : "_Q_flt";
      break;

    case LE:
      qpfunc = (TARGET_ARCH64) ? "_Qp_fle" : "_Q_fle";
      break;

    case ORDERED:
    case UNORDERED:
    case UNGT:
    case UNLT:
    case UNEQ:
    case UNGE:
    case UNLE:
    case LTGT:
      qpfunc = (TARGET_ARCH64) ? "_Qp_cmp" : "_Q_cmp";
      break;

    default:
      gcc_unreachable ();
    }

  if (TARGET_ARCH64)
    {
      if (GET_CODE (x) != MEM)
	{
	  slot0 = assign_stack_temp (TFmode, GET_MODE_SIZE(TFmode), 0);
	  emit_move_insn (slot0, x);
	}
      else
	slot0 = x;

      if (GET_CODE (y) != MEM)
	{
	  slot1 = assign_stack_temp (TFmode, GET_MODE_SIZE(TFmode), 0);
	  emit_move_insn (slot1, y);
	}
      else
	slot1 = y;

      emit_library_call (gen_rtx_SYMBOL_REF (Pmode, qpfunc), LCT_NORMAL,
			 DImode, 2,
			 XEXP (slot0, 0), Pmode,
			 XEXP (slot1, 0), Pmode);

      mode = DImode;
    }
  else
    {
      emit_library_call (gen_rtx_SYMBOL_REF (Pmode, qpfunc), LCT_NORMAL,
			 SImode, 2,
			 x, TFmode, y, TFmode);

      mode = SImode;
    }


  /* Immediately move the result of the libcall into a pseudo
     register so reload doesn't clobber the value if it needs
     the return register for a spill reg.  */
  result = gen_reg_rtx (mode);
  emit_move_insn (result, hard_libcall_value (mode));

  switch (comparison)
    {
    default:
      emit_cmp_insn (result, const0_rtx, NE, NULL_RTX, mode, 0);
      break;
    case ORDERED:
    case UNORDERED:
      emit_cmp_insn (result, GEN_INT(3), comparison == UNORDERED ? EQ : NE,
		     NULL_RTX, mode, 0);
      break;
    case UNGT:
    case UNGE:
      emit_cmp_insn (result, const1_rtx,
		     comparison == UNGT ? GT : NE, NULL_RTX, mode, 0);
      break;
    case UNLE:
      emit_cmp_insn (result, const2_rtx, NE, NULL_RTX, mode, 0);
      break;
    case UNLT:
      tem = gen_reg_rtx (mode);
      if (TARGET_ARCH32)
	emit_insn (gen_andsi3 (tem, result, const1_rtx));
      else
	emit_insn (gen_anddi3 (tem, result, const1_rtx));
      emit_cmp_insn (tem, const0_rtx, NE, NULL_RTX, mode, 0);
      break;
    case UNEQ:
    case LTGT:
      tem = gen_reg_rtx (mode);
      if (TARGET_ARCH32)
	emit_insn (gen_addsi3 (tem, result, const1_rtx));
      else
	emit_insn (gen_adddi3 (tem, result, const1_rtx));
      tem2 = gen_reg_rtx (mode);
      if (TARGET_ARCH32)
	emit_insn (gen_andsi3 (tem2, tem, const2_rtx));
      else
	emit_insn (gen_anddi3 (tem2, tem, const2_rtx));
      emit_cmp_insn (tem2, const0_rtx, comparison == UNEQ ? EQ : NE,
		     NULL_RTX, mode, 0);
      break;
    }
}