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
typedef  enum tls_model { ____Placeholder_tls_model } tls_model ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCT_CONST ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int /*<<< orphan*/  PLUS ; 
 scalar_t__ Pmode ; 
 int /*<<< orphan*/  TARGET_TLS64 ; 
#define  TLS_MODEL_GLOBAL_DYNAMIC 131 
#define  TLS_MODEL_INITIAL_EXEC 130 
#define  TLS_MODEL_LOCAL_DYNAMIC 129 
#define  TLS_MODEL_LOCAL_EXEC 128 
 int /*<<< orphan*/  UNSPEC_LD_BASE ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_libcall_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_library_call_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  expand_simple_binop (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_add_dtprel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_add_tprel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_dtpmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_dtprel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_tprel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_thread_pointer () ; 
 int /*<<< orphan*/  gen_tls_get_addr () ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  register_operand (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
ia64_expand_tls_address (enum tls_model tls_kind, rtx op0, rtx op1,
			 rtx orig_op1, HOST_WIDE_INT addend)
{
  rtx tga_op1, tga_op2, tga_ret, tga_eqv, tmp, insns;
  rtx orig_op0 = op0;
  HOST_WIDE_INT addend_lo, addend_hi;

  switch (tls_kind)
    {
    case TLS_MODEL_GLOBAL_DYNAMIC:
      start_sequence ();

      tga_op1 = gen_reg_rtx (Pmode);
      emit_insn (gen_load_dtpmod (tga_op1, op1));

      tga_op2 = gen_reg_rtx (Pmode);
      emit_insn (gen_load_dtprel (tga_op2, op1));

      tga_ret = emit_library_call_value (gen_tls_get_addr (), NULL_RTX,
					 LCT_CONST, Pmode, 2, tga_op1,
					 Pmode, tga_op2, Pmode);

      insns = get_insns ();
      end_sequence ();

      if (GET_MODE (op0) != Pmode)
	op0 = tga_ret;
      emit_libcall_block (insns, op0, tga_ret, op1);
      break;

    case TLS_MODEL_LOCAL_DYNAMIC:
      /* ??? This isn't the completely proper way to do local-dynamic
	 If the call to __tls_get_addr is used only by a single symbol,
	 then we should (somehow) move the dtprel to the second arg
	 to avoid the extra add.  */
      start_sequence ();

      tga_op1 = gen_reg_rtx (Pmode);
      emit_insn (gen_load_dtpmod (tga_op1, op1));

      tga_op2 = const0_rtx;

      tga_ret = emit_library_call_value (gen_tls_get_addr (), NULL_RTX,
					 LCT_CONST, Pmode, 2, tga_op1,
					 Pmode, tga_op2, Pmode);

      insns = get_insns ();
      end_sequence ();

      tga_eqv = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, const0_rtx),
				UNSPEC_LD_BASE);
      tmp = gen_reg_rtx (Pmode);
      emit_libcall_block (insns, tmp, tga_ret, tga_eqv);

      if (!register_operand (op0, Pmode))
	op0 = gen_reg_rtx (Pmode);
      if (TARGET_TLS64)
	{
	  emit_insn (gen_load_dtprel (op0, op1));
	  emit_insn (gen_adddi3 (op0, tmp, op0));
	}
      else
	emit_insn (gen_add_dtprel (op0, op1, tmp));
      break;

    case TLS_MODEL_INITIAL_EXEC:
      addend_lo = ((addend & 0x3fff) ^ 0x2000) - 0x2000;
      addend_hi = addend - addend_lo;

      op1 = plus_constant (op1, addend_hi);
      addend = addend_lo;

      tmp = gen_reg_rtx (Pmode);
      emit_insn (gen_load_tprel (tmp, op1));

      if (!register_operand (op0, Pmode))
	op0 = gen_reg_rtx (Pmode);
      emit_insn (gen_adddi3 (op0, tmp, gen_thread_pointer ()));
      break;

    case TLS_MODEL_LOCAL_EXEC:
      if (!register_operand (op0, Pmode))
	op0 = gen_reg_rtx (Pmode);

      op1 = orig_op1;
      addend = 0;
      if (TARGET_TLS64)
	{
	  emit_insn (gen_load_tprel (op0, op1));
	  emit_insn (gen_adddi3 (op0, op0, gen_thread_pointer ()));
	}
      else
	emit_insn (gen_add_tprel (op0, op1, gen_thread_pointer ()));
      break;

    default:
      gcc_unreachable ();
    }

  if (addend)
    op0 = expand_simple_binop (Pmode, PLUS, op0, GEN_INT (addend),
			       orig_op0, 1, OPTAB_DIRECT);
  if (orig_op0 == op0)
    return NULL_RTX;
  if (GET_MODE (orig_op0) == Pmode)
    return op0;
  return gen_lowpart (GET_MODE (orig_op0), op0);
}