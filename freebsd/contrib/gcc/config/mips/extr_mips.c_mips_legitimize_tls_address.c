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

/* Variables and functions */
 int /*<<< orphan*/  DImode ; 
 scalar_t__ GP_RETURN ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SYMBOL_DTPREL ; 
 int /*<<< orphan*/  SYMBOL_GOTTPREL ; 
 int SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_TLSGD ; 
 int /*<<< orphan*/  SYMBOL_TLSLDM ; 
 int /*<<< orphan*/  SYMBOL_TPREL ; 
 int /*<<< orphan*/  TARGET_ABICALLS ; 
#define  TLS_MODEL_GLOBAL_DYNAMIC 131 
#define  TLS_MODEL_INITIAL_EXEC 130 
#define  TLS_MODEL_LOCAL_DYNAMIC 129 
#define  TLS_MODEL_LOCAL_EXEC 128 
 int /*<<< orphan*/  UNSPEC_TLS_LDM ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_libcall_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_add3_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_gotdi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_gotsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LO_SUM (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tls_get_tp_di (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tls_get_tp_si (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_call_tls_get_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_unspec_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_unspec_offset_high (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 

__attribute__((used)) static rtx
mips_legitimize_tls_address (rtx loc)
{
  rtx dest, insn, v0, v1, tmp1, tmp2, eqv;
  enum tls_model model;

  v0 = gen_rtx_REG (Pmode, GP_RETURN);
  v1 = gen_rtx_REG (Pmode, GP_RETURN + 1);

  model = SYMBOL_REF_TLS_MODEL (loc);
  /* Only TARGET_ABICALLS code can have more than one module; other
     code must be be static and should not use a GOT.  All TLS models
     reduce to local exec in this situation.  */
  if (!TARGET_ABICALLS)
    model = TLS_MODEL_LOCAL_EXEC;

  switch (model)
    {
    case TLS_MODEL_GLOBAL_DYNAMIC:
      insn = mips_call_tls_get_addr (loc, SYMBOL_TLSGD, v0);
      dest = gen_reg_rtx (Pmode);
      emit_libcall_block (insn, dest, v0, loc);
      break;

    case TLS_MODEL_LOCAL_DYNAMIC:
      insn = mips_call_tls_get_addr (loc, SYMBOL_TLSLDM, v0);
      tmp1 = gen_reg_rtx (Pmode);

      /* Attach a unique REG_EQUIV, to allow the RTL optimizers to
	 share the LDM result with other LD model accesses.  */
      eqv = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, const0_rtx),
			    UNSPEC_TLS_LDM);
      emit_libcall_block (insn, tmp1, v0, eqv);

      tmp2 = mips_unspec_offset_high (NULL, tmp1, loc, SYMBOL_DTPREL);
      dest = gen_rtx_LO_SUM (Pmode, tmp2,
			     mips_unspec_address (loc, SYMBOL_DTPREL));
      break;

    case TLS_MODEL_INITIAL_EXEC:
      tmp1 = gen_reg_rtx (Pmode);
      tmp2 = mips_unspec_address (loc, SYMBOL_GOTTPREL);
      if (Pmode == DImode)
	{
	  emit_insn (gen_tls_get_tp_di (v1));
	  emit_insn (gen_load_gotdi (tmp1, pic_offset_table_rtx, tmp2));
	}
      else
	{
	  emit_insn (gen_tls_get_tp_si (v1));
	  emit_insn (gen_load_gotsi (tmp1, pic_offset_table_rtx, tmp2));
	}
      dest = gen_reg_rtx (Pmode);
      emit_insn (gen_add3_insn (dest, tmp1, v1));
      break;

    case TLS_MODEL_LOCAL_EXEC:
      if (Pmode == DImode)
	emit_insn (gen_tls_get_tp_di (v1));
      else
	emit_insn (gen_tls_get_tp_si (v1));

      tmp1 = mips_unspec_offset_high (NULL, v1, loc, SYMBOL_TPREL);
      dest = gen_rtx_LO_SUM (Pmode, tmp1,
			     mips_unspec_address (loc, SYMBOL_TPREL));
      break;

    default:
      gcc_unreachable ();
    }

  return dest;
}