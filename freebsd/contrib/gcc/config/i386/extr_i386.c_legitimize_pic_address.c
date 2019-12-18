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

/* Variables and functions */
 scalar_t__ CM_SMALL_PIC ; 
 scalar_t__ CONST ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_TLS_MODEL (scalar_t__) ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_MACHO ; 
 scalar_t__ UNSPEC ; 
 int /*<<< orphan*/  UNSPEC_GOT ; 
 int /*<<< orphan*/  UNSPEC_GOTOFF ; 
 int /*<<< orphan*/  UNSPEC_GOTPCREL ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_simple_binop (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_const_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gen_movsi (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__) ; 
 scalar_t__ gen_rtx_CONST (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ix86_GOT_alias_set () ; 
 scalar_t__ ix86_cmodel ; 
 scalar_t__ legitimate_pic_address_disp_p (scalar_t__) ; 
 scalar_t__ local_symbolic_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ machopic_legitimize_pic_address (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pic_offset_table_rtx ; 
 scalar_t__ plus_constant (scalar_t__,int) ; 
 int* regs_ever_live ; 
 scalar_t__ reload_in_progress ; 
 int /*<<< orphan*/  set_mem_alias_set (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x86_64_immediate_operand (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
legitimize_pic_address (rtx orig, rtx reg)
{
  rtx addr = orig;
  rtx new = orig;
  rtx base;

#if TARGET_MACHO
  if (TARGET_MACHO && !TARGET_64BIT)
    {
      if (reg == 0)
	reg = gen_reg_rtx (Pmode);
      /* Use the generic Mach-O PIC machinery.  */
      return machopic_legitimize_pic_address (orig, GET_MODE (orig), reg);
    }
#endif

  if (TARGET_64BIT && legitimate_pic_address_disp_p (addr))
    new = addr;
  else if (TARGET_64BIT
	   && ix86_cmodel != CM_SMALL_PIC
	   && local_symbolic_operand (addr, Pmode))
    {
      rtx tmpreg;
      /* This symbol may be referenced via a displacement from the PIC
	 base address (@GOTOFF).  */

      if (reload_in_progress)
	regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;
      if (GET_CODE (addr) == CONST)
	addr = XEXP (addr, 0);
      if (GET_CODE (addr) == PLUS)
	  {
            new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, XEXP (addr, 0)), UNSPEC_GOTOFF);
	    new = gen_rtx_PLUS (Pmode, new, XEXP (addr, 1));
	  }
	else
          new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOTOFF);
      new = gen_rtx_CONST (Pmode, new);
      if (!reg)
        tmpreg = gen_reg_rtx (Pmode);
      else
	tmpreg = reg;
      emit_move_insn (tmpreg, new);

      if (reg != 0)
	{
	  new = expand_simple_binop (Pmode, PLUS, reg, pic_offset_table_rtx,
				     tmpreg, 1, OPTAB_DIRECT);
	  new = reg;
	}
      else new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, tmpreg);
    }
  else if (!TARGET_64BIT && local_symbolic_operand (addr, Pmode))
    {
      /* This symbol may be referenced via a displacement from the PIC
	 base address (@GOTOFF).  */

      if (reload_in_progress)
	regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;
      if (GET_CODE (addr) == CONST)
	addr = XEXP (addr, 0);
      if (GET_CODE (addr) == PLUS)
	  {
            new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, XEXP (addr, 0)), UNSPEC_GOTOFF);
	    new = gen_rtx_PLUS (Pmode, new, XEXP (addr, 1));
	  }
	else
          new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOTOFF);
      new = gen_rtx_CONST (Pmode, new);
      new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, new);

      if (reg != 0)
	{
	  emit_move_insn (reg, new);
	  new = reg;
	}
    }
  else if (GET_CODE (addr) == SYMBOL_REF && SYMBOL_REF_TLS_MODEL (addr) == 0)
    {
      if (TARGET_64BIT)
	{
	  new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOTPCREL);
	  new = gen_rtx_CONST (Pmode, new);
	  new = gen_const_mem (Pmode, new);
	  set_mem_alias_set (new, ix86_GOT_alias_set ());

	  if (reg == 0)
	    reg = gen_reg_rtx (Pmode);
	  /* Use directly gen_movsi, otherwise the address is loaded
	     into register for CSE.  We don't want to CSE this addresses,
	     instead we CSE addresses from the GOT table, so skip this.  */
	  emit_insn (gen_movsi (reg, new));
	  new = reg;
	}
      else
	{
	  /* This symbol must be referenced via a load from the
	     Global Offset Table (@GOT).  */

	  if (reload_in_progress)
	    regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;
	  new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOT);
	  new = gen_rtx_CONST (Pmode, new);
	  new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, new);
	  new = gen_const_mem (Pmode, new);
	  set_mem_alias_set (new, ix86_GOT_alias_set ());

	  if (reg == 0)
	    reg = gen_reg_rtx (Pmode);
	  emit_move_insn (reg, new);
	  new = reg;
	}
    }
  else
    {
      if (GET_CODE (addr) == CONST_INT
	  && !x86_64_immediate_operand (addr, VOIDmode))
	{
	  if (reg)
	    {
	      emit_move_insn (reg, addr);
	      new = reg;
	    }
	  else
	    new = force_reg (Pmode, addr);
	}
      else if (GET_CODE (addr) == CONST)
	{
	  addr = XEXP (addr, 0);

	  /* We must match stuff we generate before.  Assume the only
	     unspecs that can get here are ours.  Not that we could do
	     anything with them anyway....  */
	  if (GET_CODE (addr) == UNSPEC
	      || (GET_CODE (addr) == PLUS
		  && GET_CODE (XEXP (addr, 0)) == UNSPEC))
	    return orig;
	  gcc_assert (GET_CODE (addr) == PLUS);
	}
      if (GET_CODE (addr) == PLUS)
	{
	  rtx op0 = XEXP (addr, 0), op1 = XEXP (addr, 1);

	  /* Check first to see if this is a constant offset from a @GOTOFF
	     symbol reference.  */
	  if (local_symbolic_operand (op0, Pmode)
	      && GET_CODE (op1) == CONST_INT)
	    {
	      if (!TARGET_64BIT)
		{
		  if (reload_in_progress)
		    regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;
		  new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, op0),
					UNSPEC_GOTOFF);
		  new = gen_rtx_PLUS (Pmode, new, op1);
		  new = gen_rtx_CONST (Pmode, new);
		  new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, new);

		  if (reg != 0)
		    {
		      emit_move_insn (reg, new);
		      new = reg;
		    }
		}
	      else
		{
		  if (INTVAL (op1) < -16*1024*1024
		      || INTVAL (op1) >= 16*1024*1024)
		    {
		      if (!x86_64_immediate_operand (op1, Pmode))
			op1 = force_reg (Pmode, op1);
		      new = gen_rtx_PLUS (Pmode, force_reg (Pmode, op0), op1);
		    }
		}
	    }
	  else
	    {
	      base = legitimize_pic_address (XEXP (addr, 0), reg);
	      new  = legitimize_pic_address (XEXP (addr, 1),
					     base == reg ? NULL_RTX : reg);

	      if (GET_CODE (new) == CONST_INT)
		new = plus_constant (base, INTVAL (new));
	      else
		{
		  if (GET_CODE (new) == PLUS && CONSTANT_P (XEXP (new, 1)))
		    {
		      base = gen_rtx_PLUS (Pmode, base, XEXP (new, 0));
		      new = XEXP (new, 1);
		    }
		  new = gen_rtx_PLUS (Pmode, base, new);
		}
	    }
	}
    }
  return new;
}