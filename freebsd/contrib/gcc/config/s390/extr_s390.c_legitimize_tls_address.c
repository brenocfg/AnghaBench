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

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  TARGET_CPU_ZARCH ; 
#define  TLS_MODEL_GLOBAL_DYNAMIC 132 
#define  TLS_MODEL_INITIAL_EXEC 131 
#define  TLS_MODEL_LOCAL_DYNAMIC 130 
#define  TLS_MODEL_LOCAL_EXEC 129 
 scalar_t__ UNSPEC ; 
 int UNSPEC_DTPOFF ; 
 int UNSPEC_GOTNTPOFF ; 
#define  UNSPEC_INDNTPOFF 128 
 int UNSPEC_NTPOFF ; 
 int UNSPEC_TLSGD ; 
 int UNSPEC_TLSLDM ; 
 int UNSPEC_TLSLDM_NTPOFF ; 
 int UNSPEC_TLS_LOAD ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_libcall_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int flag_pic ; 
 int /*<<< orphan*/  force_const_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_const_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gen_rtx_CONST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* regs_ever_live ; 
 int /*<<< orphan*/  reload_completed ; 
 int /*<<< orphan*/  reload_in_progress ; 
 int /*<<< orphan*/  s390_emit_tls_call_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s390_get_thread_pointer () ; 
 int /*<<< orphan*/  s390_load_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 
 int tls_symbolic_operand (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
legitimize_tls_address (rtx addr, rtx reg)
{
  rtx new, tls_call, temp, base, r2, insn;

  if (GET_CODE (addr) == SYMBOL_REF)
    switch (tls_symbolic_operand (addr))
      {
      case TLS_MODEL_GLOBAL_DYNAMIC:
	start_sequence ();
	r2 = gen_rtx_REG (Pmode, 2);
	tls_call = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_TLSGD);
	new = gen_rtx_CONST (Pmode, tls_call);
	new = force_const_mem (Pmode, new);
	emit_move_insn (r2, new);
	s390_emit_tls_call_insn (r2, tls_call);
	insn = get_insns ();
	end_sequence ();

	new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_NTPOFF);
	temp = gen_reg_rtx (Pmode);
	emit_libcall_block (insn, temp, r2, new);

	new = gen_rtx_PLUS (Pmode, s390_get_thread_pointer (), temp);
	if (reg != 0)
	  {
	    s390_load_address (reg, new);
	    new = reg;
	  }
	break;

      case TLS_MODEL_LOCAL_DYNAMIC:
	start_sequence ();
	r2 = gen_rtx_REG (Pmode, 2);
	tls_call = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, const0_rtx), UNSPEC_TLSLDM);
	new = gen_rtx_CONST (Pmode, tls_call);
	new = force_const_mem (Pmode, new);
	emit_move_insn (r2, new);
	s390_emit_tls_call_insn (r2, tls_call);
	insn = get_insns ();
	end_sequence ();

	new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, const0_rtx), UNSPEC_TLSLDM_NTPOFF);
	temp = gen_reg_rtx (Pmode);
	emit_libcall_block (insn, temp, r2, new);

	new = gen_rtx_PLUS (Pmode, s390_get_thread_pointer (), temp);
	base = gen_reg_rtx (Pmode);
	s390_load_address (base, new);

	new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_DTPOFF);
	new = gen_rtx_CONST (Pmode, new);
	new = force_const_mem (Pmode, new);
	temp = gen_reg_rtx (Pmode);
	emit_move_insn (temp, new);

	new = gen_rtx_PLUS (Pmode, base, temp);
	if (reg != 0)
	  {
	    s390_load_address (reg, new);
	    new = reg;
	  }
	break;

      case TLS_MODEL_INITIAL_EXEC:
	if (flag_pic == 1)
	  {
	    /* Assume GOT offset < 4k.  This is handled the same way
	       in both 31- and 64-bit code.  */

	    if (reload_in_progress || reload_completed)
	      regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;

	    new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOTNTPOFF);
	    new = gen_rtx_CONST (Pmode, new);
	    new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, new);
	    new = gen_const_mem (Pmode, new);
	    temp = gen_reg_rtx (Pmode);
	    emit_move_insn (temp, new);
	  }
	else if (TARGET_CPU_ZARCH)
	  {
	    /* If the GOT offset might be >= 4k, we determine the position
	       of the GOT entry via a PC-relative LARL.  */

	    new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_INDNTPOFF);
	    new = gen_rtx_CONST (Pmode, new);
	    temp = gen_reg_rtx (Pmode);
	    emit_move_insn (temp, new);

	    new = gen_const_mem (Pmode, temp);
	    temp = gen_reg_rtx (Pmode);
	    emit_move_insn (temp, new);
	  }
	else if (flag_pic)
	  {
	    /* If the GOT offset might be >= 4k, we have to load it
	       from the literal pool.  */

	    if (reload_in_progress || reload_completed)
	      regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;

	    new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOTNTPOFF);
	    new = gen_rtx_CONST (Pmode, new);
	    new = force_const_mem (Pmode, new);
	    temp = gen_reg_rtx (Pmode);
	    emit_move_insn (temp, new);

            new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, temp);
	    new = gen_const_mem (Pmode, new);

	    new = gen_rtx_UNSPEC (Pmode, gen_rtvec (2, new, addr), UNSPEC_TLS_LOAD);
	    temp = gen_reg_rtx (Pmode);
	    emit_insn (gen_rtx_SET (Pmode, temp, new));
	  }
	else
	  {
	    /* In position-dependent code, load the absolute address of
	       the GOT entry from the literal pool.  */

	    new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_INDNTPOFF);
	    new = gen_rtx_CONST (Pmode, new);
	    new = force_const_mem (Pmode, new);
	    temp = gen_reg_rtx (Pmode);
	    emit_move_insn (temp, new);

	    new = temp;
	    new = gen_const_mem (Pmode, new);
	    new = gen_rtx_UNSPEC (Pmode, gen_rtvec (2, new, addr), UNSPEC_TLS_LOAD);
	    temp = gen_reg_rtx (Pmode);
	    emit_insn (gen_rtx_SET (Pmode, temp, new));
	  }

	new = gen_rtx_PLUS (Pmode, s390_get_thread_pointer (), temp);
	if (reg != 0)
	  {
	    s390_load_address (reg, new);
	    new = reg;
	  }
	break;

      case TLS_MODEL_LOCAL_EXEC:
	new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_NTPOFF);
	new = gen_rtx_CONST (Pmode, new);
	new = force_const_mem (Pmode, new);
        temp = gen_reg_rtx (Pmode);
	emit_move_insn (temp, new);

	new = gen_rtx_PLUS (Pmode, s390_get_thread_pointer (), temp);
	if (reg != 0)
	  {
	    s390_load_address (reg, new);
	    new = reg;
	  }
	break;

      default:
	gcc_unreachable ();
      }

  else if (GET_CODE (addr) == CONST && GET_CODE (XEXP (addr, 0)) == UNSPEC)
    {
      switch (XINT (XEXP (addr, 0), 1))
	{
	case UNSPEC_INDNTPOFF:
	  gcc_assert (TARGET_CPU_ZARCH);
	  new = addr;
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  else if (GET_CODE (addr) == CONST && GET_CODE (XEXP (addr, 0)) == PLUS
	   && GET_CODE (XEXP (XEXP (addr, 0), 1)) == CONST_INT)
    {
      new = XEXP (XEXP (addr, 0), 0);
      if (GET_CODE (new) != SYMBOL_REF)
	new = gen_rtx_CONST (Pmode, new);

      new = legitimize_tls_address (new, reg);
      new = plus_constant (new, INTVAL (XEXP (XEXP (addr, 0), 1)));
      new = force_operand (new, 0);
    }

  else
    gcc_unreachable ();  /* for now ... */

  return new;
}