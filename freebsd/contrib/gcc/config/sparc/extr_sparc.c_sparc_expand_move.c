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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ CONST0_RTX (int) ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 int DFmode ; 
#define  DImode 131 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ HIGH ; 
#define  HImode 130 
 scalar_t__ LABEL_REF ; 
 scalar_t__ MEM ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PLUS ; 
#define  QImode 129 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 int SFmode ; 
#define  SImode 128 
 scalar_t__ SPARC_FIRST_FP_REG ; 
 scalar_t__ SPARC_FP_REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SPARC_SYMBOL_REF_TLS_P (scalar_t__) ; 
 int /*<<< orphan*/  TARGET_ARCH64 ; 
 scalar_t__ TARGET_HAVE_TLS ; 
 scalar_t__ TARGET_VIS ; 
 scalar_t__ VECTOR_MODE_P (int) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const_zero_operand (scalar_t__,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_pic ; 
 scalar_t__ force_const_mem (int,scalar_t__) ; 
 scalar_t__ force_operand (scalar_t__,scalar_t__) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_movdi_pic_label_ref (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_movsi_pic_label_ref (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int,scalar_t__,scalar_t__) ; 
 scalar_t__ input_operand (scalar_t__,int) ; 
 scalar_t__ legitimize_pic_address (scalar_t__,int,scalar_t__) ; 
 scalar_t__ legitimize_tls_address (scalar_t__) ; 
 scalar_t__ pic_address_needs_scratch (scalar_t__) ; 
 scalar_t__ register_or_zero_operand (scalar_t__,int) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 int /*<<< orphan*/  sparc_emit_set_const32 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sparc_emit_set_const64 (scalar_t__,scalar_t__) ; 
 scalar_t__ sparc_tls_referenced_p (scalar_t__) ; 
 scalar_t__ symbolic_operand (scalar_t__,int) ; 
 scalar_t__ validize_mem (scalar_t__) ; 

bool
sparc_expand_move (enum machine_mode mode, rtx *operands)
{
  /* Handle sets of MEM first.  */
  if (GET_CODE (operands[0]) == MEM)
    {
      /* 0 is a register (or a pair of registers) on SPARC.  */
      if (register_or_zero_operand (operands[1], mode))
	return false;

      if (!reload_in_progress)
	{
	  operands[0] = validize_mem (operands[0]);
	  operands[1] = force_reg (mode, operands[1]);
	}
    }

  /* Fixup TLS cases.  */
  if (TARGET_HAVE_TLS
      && CONSTANT_P (operands[1])
      && GET_CODE (operands[1]) != HIGH
      && sparc_tls_referenced_p (operands [1]))
    {
      rtx sym = operands[1];
      rtx addend = NULL;

      if (GET_CODE (sym) == CONST && GET_CODE (XEXP (sym, 0)) == PLUS)
	{
	  addend = XEXP (XEXP (sym, 0), 1);
	  sym = XEXP (XEXP (sym, 0), 0);
	}

      gcc_assert (SPARC_SYMBOL_REF_TLS_P (sym));

      sym = legitimize_tls_address (sym);
      if (addend)
	{
	  sym = gen_rtx_PLUS (mode, sym, addend);
	  sym = force_operand (sym, operands[0]);
	}
      operands[1] = sym;
    }
 
  /* Fixup PIC cases.  */
  if (flag_pic && CONSTANT_P (operands[1]))
    {
      if (pic_address_needs_scratch (operands[1]))
	operands[1] = legitimize_pic_address (operands[1], mode, 0);

      if (GET_CODE (operands[1]) == LABEL_REF && mode == SImode)
	{
	  emit_insn (gen_movsi_pic_label_ref (operands[0], operands[1]));
	  return true;
	}

      if (GET_CODE (operands[1]) == LABEL_REF && mode == DImode)
	{
	  gcc_assert (TARGET_ARCH64);
	  emit_insn (gen_movdi_pic_label_ref (operands[0], operands[1]));
	  return true;
	}

      if (symbolic_operand (operands[1], mode))
	{
	  operands[1] = legitimize_pic_address (operands[1],
						mode,
						(reload_in_progress ?
						 operands[0] :
						 NULL_RTX));
	  return false;
	}
    }

  /* If we are trying to toss an integer constant into FP registers,
     or loading a FP or vector constant, force it into memory.  */
  if (CONSTANT_P (operands[1])
      && REG_P (operands[0])
      && (SPARC_FP_REG_P (REGNO (operands[0]))
	  || SCALAR_FLOAT_MODE_P (mode)
	  || VECTOR_MODE_P (mode)))
    {
      /* emit_group_store will send such bogosity to us when it is
         not storing directly into memory.  So fix this up to avoid
         crashes in output_constant_pool.  */
      if (operands [1] == const0_rtx)
	operands[1] = CONST0_RTX (mode);

      /* We can clear FP registers if TARGET_VIS, and always other regs.  */
      if ((TARGET_VIS || REGNO (operands[0]) < SPARC_FIRST_FP_REG)
	  && const_zero_operand (operands[1], mode))
	return false;

      if (REGNO (operands[0]) < SPARC_FIRST_FP_REG
	  /* We are able to build any SF constant in integer registers
	     with at most 2 instructions.  */
	  && (mode == SFmode
	      /* And any DF constant in integer registers.  */
	      || (mode == DFmode
		  && (reload_completed || reload_in_progress))))
	return false;

      operands[1] = force_const_mem (mode, operands[1]);
      if (!reload_in_progress)
	operands[1] = validize_mem (operands[1]);
      return false;
    }

  /* Accept non-constants and valid constants unmodified.  */
  if (!CONSTANT_P (operands[1])
      || GET_CODE (operands[1]) == HIGH
      || input_operand (operands[1], mode))
    return false;

  switch (mode)
    {
    case QImode:
      /* All QImode constants require only one insn, so proceed.  */
      break;

    case HImode:
    case SImode:
      sparc_emit_set_const32 (operands[0], operands[1]);
      return true;

    case DImode:
      /* input_operand should have filtered out 32-bit mode.  */
      sparc_emit_set_const64 (operands[0], operands[1]);
      return true;
    
    default:
      gcc_unreachable ();
    }

  return false;
}