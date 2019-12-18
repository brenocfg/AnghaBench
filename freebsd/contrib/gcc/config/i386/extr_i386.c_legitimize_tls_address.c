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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum tls_model { ____Placeholder_tls_model } tls_model ;

/* Variables and functions */
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  REG_EQUIV ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_ANY_GNU_TLS ; 
 int /*<<< orphan*/  TARGET_GNU2_TLS ; 
 int /*<<< orphan*/  TARGET_TLS_DIRECT_SEG_REFS ; 
#define  TLS_MODEL_GLOBAL_DYNAMIC 131 
#define  TLS_MODEL_INITIAL_EXEC 130 
#define  TLS_MODEL_LOCAL_DYNAMIC 129 
#define  TLS_MODEL_LOCAL_EXEC 128 
 int UNSPEC_DTPOFF ; 
 int UNSPEC_GOTNTPOFF ; 
 int UNSPEC_GOTTPOFF ; 
 int UNSPEC_INDNTPOFF ; 
 int UNSPEC_NTPOFF ; 
 int UNSPEC_TPOFF ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_call_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_libcall_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  flag_pic ; 
 int /*<<< orphan*/ * force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * gen_const_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_CONST (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_MINUS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_set_got (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_subsi3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_tls_global_dynamic_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_tls_global_dynamic_64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_tls_local_dynamic_base_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_tls_local_dynamic_base_64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_insns () ; 
 int /*<<< orphan*/  get_last_insn () ; 
 int /*<<< orphan*/ * get_thread_pointer (int) ; 
 int /*<<< orphan*/  ix86_GOT_alias_set () ; 
 int /*<<< orphan*/  ix86_tls_get_addr () ; 
 int /*<<< orphan*/ * ix86_tls_module_base () ; 
 int /*<<< orphan*/ * pic_offset_table_rtx ; 
 int* regs_ever_live ; 
 int /*<<< orphan*/  reload_in_progress ; 
 int /*<<< orphan*/  set_mem_alias_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unique_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
legitimize_tls_address (rtx x, enum tls_model model, int for_mov)
{
  rtx dest, base, off, pic, tp;
  int type;

  switch (model)
    {
    case TLS_MODEL_GLOBAL_DYNAMIC:
      dest = gen_reg_rtx (Pmode);
      tp = TARGET_GNU2_TLS ? get_thread_pointer (1) : 0;

      if (TARGET_64BIT && ! TARGET_GNU2_TLS)
	{
	  rtx rax = gen_rtx_REG (Pmode, 0), insns;

	  start_sequence ();
	  emit_call_insn (gen_tls_global_dynamic_64 (rax, x));
	  insns = get_insns ();
	  end_sequence ();

	  emit_libcall_block (insns, dest, rax, x);
	}
      else if (TARGET_64BIT && TARGET_GNU2_TLS)
	emit_insn (gen_tls_global_dynamic_64 (dest, x));
      else
	emit_insn (gen_tls_global_dynamic_32 (dest, x));

      if (TARGET_GNU2_TLS)
	{
	  dest = force_reg (Pmode, gen_rtx_PLUS (Pmode, tp, dest));

	  set_unique_reg_note (get_last_insn (), REG_EQUIV, x);
	}
      break;

    case TLS_MODEL_LOCAL_DYNAMIC:
      base = gen_reg_rtx (Pmode);
      tp = TARGET_GNU2_TLS ? get_thread_pointer (1) : 0;

      if (TARGET_64BIT && ! TARGET_GNU2_TLS)
	{
	  rtx rax = gen_rtx_REG (Pmode, 0), insns, note;

	  start_sequence ();
	  emit_call_insn (gen_tls_local_dynamic_base_64 (rax));
	  insns = get_insns ();
	  end_sequence ();

	  note = gen_rtx_EXPR_LIST (VOIDmode, const0_rtx, NULL);
	  note = gen_rtx_EXPR_LIST (VOIDmode, ix86_tls_get_addr (), note);
	  emit_libcall_block (insns, base, rax, note);
	}
      else if (TARGET_64BIT && TARGET_GNU2_TLS)
	emit_insn (gen_tls_local_dynamic_base_64 (base));
      else
	emit_insn (gen_tls_local_dynamic_base_32 (base));

      if (TARGET_GNU2_TLS)
	{
	  rtx x = ix86_tls_module_base ();

	  set_unique_reg_note (get_last_insn (), REG_EQUIV,
			       gen_rtx_MINUS (Pmode, x, tp));
	}

      off = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, x), UNSPEC_DTPOFF);
      off = gen_rtx_CONST (Pmode, off);

      dest = force_reg (Pmode, gen_rtx_PLUS (Pmode, base, off));

      if (TARGET_GNU2_TLS)
	{
	  dest = force_reg (Pmode, gen_rtx_PLUS (Pmode, dest, tp));

	  set_unique_reg_note (get_last_insn (), REG_EQUIV, x);
	}

      break;

    case TLS_MODEL_INITIAL_EXEC:
      if (TARGET_64BIT)
	{
	  pic = NULL;
	  type = UNSPEC_GOTNTPOFF;
	}
      else if (flag_pic)
	{
	  if (reload_in_progress)
	    regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;
	  pic = pic_offset_table_rtx;
	  type = TARGET_ANY_GNU_TLS ? UNSPEC_GOTNTPOFF : UNSPEC_GOTTPOFF;
	}
      else if (!TARGET_ANY_GNU_TLS)
	{
	  pic = gen_reg_rtx (Pmode);
	  emit_insn (gen_set_got (pic));
	  type = UNSPEC_GOTTPOFF;
	}
      else
	{
	  pic = NULL;
	  type = UNSPEC_INDNTPOFF;
	}

      off = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, x), type);
      off = gen_rtx_CONST (Pmode, off);
      if (pic)
	off = gen_rtx_PLUS (Pmode, pic, off);
      off = gen_const_mem (Pmode, off);
      set_mem_alias_set (off, ix86_GOT_alias_set ());

      if (TARGET_64BIT || TARGET_ANY_GNU_TLS)
	{
          base = get_thread_pointer (for_mov || !TARGET_TLS_DIRECT_SEG_REFS);
	  off = force_reg (Pmode, off);
	  return gen_rtx_PLUS (Pmode, base, off);
	}
      else
	{
	  base = get_thread_pointer (true);
	  dest = gen_reg_rtx (Pmode);
	  emit_insn (gen_subsi3 (dest, base, off));
	}
      break;

    case TLS_MODEL_LOCAL_EXEC:
      off = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, x),
			    (TARGET_64BIT || TARGET_ANY_GNU_TLS)
			    ? UNSPEC_NTPOFF : UNSPEC_TPOFF);
      off = gen_rtx_CONST (Pmode, off);

      if (TARGET_64BIT || TARGET_ANY_GNU_TLS)
	{
	  base = get_thread_pointer (for_mov || !TARGET_TLS_DIRECT_SEG_REFS);
	  return gen_rtx_PLUS (Pmode, base, off);
	}
      else
	{
	  base = get_thread_pointer (true);
	  dest = gen_reg_rtx (Pmode);
	  emit_insn (gen_subsi3 (dest, base, off));
	}
      break;

    default:
      gcc_unreachable ();
    }

  return dest;
}