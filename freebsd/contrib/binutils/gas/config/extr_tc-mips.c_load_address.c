#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ valueT ;
struct TYPE_8__ {scalar_t__ X_op; int X_add_number; int /*<<< orphan*/  X_add_symbol; } ;
typedef  TYPE_1__ expressionS ;
struct TYPE_10__ {scalar_t__ noat; } ;
struct TYPE_9__ {scalar_t__ sequence; } ;

/* Variables and functions */
 char* ADDRESS_ADDI_INSN ; 
 char* ADDRESS_ADD_INSN ; 
 char* ADDRESS_LOAD_INSN ; 
 int AT ; 
 int BFD_RELOC_GPREL16 ; 
 int BFD_RELOC_HI16_S ; 
 int BFD_RELOC_LO16 ; 
 int BFD_RELOC_MIPS_GOT16 ; 
 int BFD_RELOC_MIPS_GOT_DISP ; 
 int /*<<< orphan*/  BFD_RELOC_MIPS_GOT_HI16 ; 
 int BFD_RELOC_MIPS_GOT_LO16 ; 
 int BFD_RELOC_MIPS_GOT_OFST ; 
 int BFD_RELOC_MIPS_GOT_PAGE ; 
 int BFD_RELOC_MIPS_HIGHER ; 
 int /*<<< orphan*/  BFD_RELOC_MIPS_HIGHEST ; 
 int /*<<< orphan*/  HAVE_64BIT_ADDRESSES ; 
 scalar_t__ HAVE_64BIT_SYMBOLS ; 
 scalar_t__ HAVE_NEWABI ; 
 scalar_t__ MAX_GPREL_OFFSET ; 
 scalar_t__ NO_PIC ; 
 scalar_t__ O_constant ; 
 scalar_t__ O_symbol ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_delay_nop () ; 
 int /*<<< orphan*/  load_register (int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macro_build (TYPE_1__*,char*,char*,...) ; 
 int /*<<< orphan*/  macro_build_lui (TYPE_1__*,int) ; 
 scalar_t__ mips_big_got ; 
 int mips_gp_register ; 
 TYPE_3__ mips_opts ; 
 scalar_t__ mips_pic ; 
 TYPE_2__ mips_relax ; 
 int /*<<< orphan*/  nopic_need_relax (int /*<<< orphan*/ ,int) ; 
 scalar_t__ reg_needs_delay (int) ; 
 int /*<<< orphan*/  relax_end () ; 
 int /*<<< orphan*/  relax_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relax_switch () ; 

__attribute__((used)) static void
load_address (int reg, expressionS *ep, int *used_at)
{
  if (ep->X_op != O_constant
      && ep->X_op != O_symbol)
    {
      as_bad (_("expression too complex"));
      ep->X_op = O_constant;
    }

  if (ep->X_op == O_constant)
    {
      load_register (reg, ep, HAVE_64BIT_ADDRESSES);
      return;
    }

  if (mips_pic == NO_PIC)
    {
      /* If this is a reference to a GP relative symbol, we want
	   addiu	$reg,$gp,<sym>		(BFD_RELOC_GPREL16)
	 Otherwise we want
	   lui		$reg,<sym>		(BFD_RELOC_HI16_S)
	   addiu	$reg,$reg,<sym>		(BFD_RELOC_LO16)
	 If we have an addend, we always use the latter form.

	 With 64bit address space and a usable $at we want
	   lui		$reg,<sym>		(BFD_RELOC_MIPS_HIGHEST)
	   lui		$at,<sym>		(BFD_RELOC_HI16_S)
	   daddiu	$reg,<sym>		(BFD_RELOC_MIPS_HIGHER)
	   daddiu	$at,<sym>		(BFD_RELOC_LO16)
	   dsll32	$reg,0
	   daddu	$reg,$reg,$at

	 If $at is already in use, we use a path which is suboptimal
	 on superscalar processors.
	   lui		$reg,<sym>		(BFD_RELOC_MIPS_HIGHEST)
	   daddiu	$reg,<sym>		(BFD_RELOC_MIPS_HIGHER)
	   dsll		$reg,16
	   daddiu	$reg,<sym>		(BFD_RELOC_HI16_S)
	   dsll		$reg,16
	   daddiu	$reg,<sym>		(BFD_RELOC_LO16)

	 For GP relative symbols in 64bit address space we can use
	 the same sequence as in 32bit address space.  */
      if (HAVE_64BIT_SYMBOLS)
	{
	  if ((valueT) ep->X_add_number <= MAX_GPREL_OFFSET
	      && !nopic_need_relax (ep->X_add_symbol, 1))
	    {
	      relax_start (ep->X_add_symbol);
	      macro_build (ep, ADDRESS_ADDI_INSN, "t,r,j", reg,
			   mips_gp_register, BFD_RELOC_GPREL16);
	      relax_switch ();
	    }

	  if (*used_at == 0 && !mips_opts.noat)
	    {
	      macro_build (ep, "lui", "t,u", reg, BFD_RELOC_MIPS_HIGHEST);
	      macro_build (ep, "lui", "t,u", AT, BFD_RELOC_HI16_S);
	      macro_build (ep, "daddiu", "t,r,j", reg, reg,
			   BFD_RELOC_MIPS_HIGHER);
	      macro_build (ep, "daddiu", "t,r,j", AT, AT, BFD_RELOC_LO16);
	      macro_build (NULL, "dsll32", "d,w,<", reg, reg, 0);
	      macro_build (NULL, "daddu", "d,v,t", reg, reg, AT);
	      *used_at = 1;
	    }
	  else
	    {
	      macro_build (ep, "lui", "t,u", reg, BFD_RELOC_MIPS_HIGHEST);
	      macro_build (ep, "daddiu", "t,r,j", reg, reg,
			   BFD_RELOC_MIPS_HIGHER);
	      macro_build (NULL, "dsll", "d,w,<", reg, reg, 16);
	      macro_build (ep, "daddiu", "t,r,j", reg, reg, BFD_RELOC_HI16_S);
	      macro_build (NULL, "dsll", "d,w,<", reg, reg, 16);
	      macro_build (ep, "daddiu", "t,r,j", reg, reg, BFD_RELOC_LO16);
	    }

	  if (mips_relax.sequence)
	    relax_end ();
	}
      else
	{
	  if ((valueT) ep->X_add_number <= MAX_GPREL_OFFSET
	      && !nopic_need_relax (ep->X_add_symbol, 1))
	    {
	      relax_start (ep->X_add_symbol);
	      macro_build (ep, ADDRESS_ADDI_INSN, "t,r,j", reg,
			   mips_gp_register, BFD_RELOC_GPREL16);
	      relax_switch ();
	    }
	  macro_build_lui (ep, reg);
	  macro_build (ep, ADDRESS_ADDI_INSN, "t,r,j",
		       reg, reg, BFD_RELOC_LO16);
	  if (mips_relax.sequence)
	    relax_end ();
	}
    }
  else if (!mips_big_got)
    {
      expressionS ex;

      /* If this is a reference to an external symbol, we want
	   lw		$reg,<sym>($gp)		(BFD_RELOC_MIPS_GOT16)
	 Otherwise we want
	   lw		$reg,<sym>($gp)		(BFD_RELOC_MIPS_GOT16)
	   nop
	   addiu	$reg,$reg,<sym>		(BFD_RELOC_LO16)
	 If there is a constant, it must be added in after.

	 If we have NewABI, we want
	   lw		$reg,<sym+cst>($gp)	(BFD_RELOC_MIPS_GOT_DISP)
         unless we're referencing a global symbol with a non-zero
         offset, in which case cst must be added separately.  */
      if (HAVE_NEWABI)
	{
	  if (ep->X_add_number)
	    {
	      ex.X_add_number = ep->X_add_number;
	      ep->X_add_number = 0;
	      relax_start (ep->X_add_symbol);
	      macro_build (ep, ADDRESS_LOAD_INSN, "t,o(b)", reg,
			   BFD_RELOC_MIPS_GOT_DISP, mips_gp_register);
	      if (ex.X_add_number < -0x8000 || ex.X_add_number >= 0x8000)
		as_bad (_("PIC code offset overflow (max 16 signed bits)"));
	      ex.X_op = O_constant;
	      macro_build (&ex, ADDRESS_ADDI_INSN, "t,r,j",
			   reg, reg, BFD_RELOC_LO16);
	      ep->X_add_number = ex.X_add_number;
	      relax_switch ();
	    }
	  macro_build (ep, ADDRESS_LOAD_INSN, "t,o(b)", reg,
		       BFD_RELOC_MIPS_GOT_DISP, mips_gp_register);
	  if (mips_relax.sequence)
	    relax_end ();
	}
      else
	{
	  ex.X_add_number = ep->X_add_number;
	  ep->X_add_number = 0;
	  macro_build (ep, ADDRESS_LOAD_INSN, "t,o(b)", reg,
		       BFD_RELOC_MIPS_GOT16, mips_gp_register);
	  load_delay_nop ();
	  relax_start (ep->X_add_symbol);
	  relax_switch ();
	  macro_build (ep, ADDRESS_ADDI_INSN, "t,r,j", reg, reg,
		       BFD_RELOC_LO16);
	  relax_end ();

	  if (ex.X_add_number != 0)
	    {
	      if (ex.X_add_number < -0x8000 || ex.X_add_number >= 0x8000)
		as_bad (_("PIC code offset overflow (max 16 signed bits)"));
	      ex.X_op = O_constant;
	      macro_build (&ex, ADDRESS_ADDI_INSN, "t,r,j",
			   reg, reg, BFD_RELOC_LO16);
	    }
	}
    }
  else if (mips_big_got)
    {
      expressionS ex;

      /* This is the large GOT case.  If this is a reference to an
	 external symbol, we want
	   lui		$reg,<sym>		(BFD_RELOC_MIPS_GOT_HI16)
	   addu		$reg,$reg,$gp
	   lw		$reg,<sym>($reg)	(BFD_RELOC_MIPS_GOT_LO16)

	 Otherwise, for a reference to a local symbol in old ABI, we want
	   lw		$reg,<sym>($gp)		(BFD_RELOC_MIPS_GOT16)
	   nop
	   addiu	$reg,$reg,<sym>		(BFD_RELOC_LO16)
	 If there is a constant, it must be added in after.

	 In the NewABI, for local symbols, with or without offsets, we want:
	   lw		$reg,<sym>($gp)		(BFD_RELOC_MIPS_GOT_PAGE)
	   addiu	$reg,$reg,<sym>		(BFD_RELOC_MIPS_GOT_OFST)
      */
      if (HAVE_NEWABI)
	{
	  ex.X_add_number = ep->X_add_number;
	  ep->X_add_number = 0;
	  relax_start (ep->X_add_symbol);
	  macro_build (ep, "lui", "t,u", reg, BFD_RELOC_MIPS_GOT_HI16);
	  macro_build (NULL, ADDRESS_ADD_INSN, "d,v,t",
		       reg, reg, mips_gp_register);
	  macro_build (ep, ADDRESS_LOAD_INSN, "t,o(b)",
		       reg, BFD_RELOC_MIPS_GOT_LO16, reg);
	  if (ex.X_add_number < -0x8000 || ex.X_add_number >= 0x8000)
	    as_bad (_("PIC code offset overflow (max 16 signed bits)"));
	  else if (ex.X_add_number)
	    {
	      ex.X_op = O_constant;
	      macro_build (&ex, ADDRESS_ADDI_INSN, "t,r,j", reg, reg,
			   BFD_RELOC_LO16);
	    }

	  ep->X_add_number = ex.X_add_number;
	  relax_switch ();
	  macro_build (ep, ADDRESS_LOAD_INSN, "t,o(b)", reg,
		       BFD_RELOC_MIPS_GOT_PAGE, mips_gp_register);
	  macro_build (ep, ADDRESS_ADDI_INSN, "t,r,j", reg, reg,
		       BFD_RELOC_MIPS_GOT_OFST);
	  relax_end ();
	}
      else
	{
	  ex.X_add_number = ep->X_add_number;
	  ep->X_add_number = 0;
	  relax_start (ep->X_add_symbol);
	  macro_build (ep, "lui", "t,u", reg, BFD_RELOC_MIPS_GOT_HI16);
	  macro_build (NULL, ADDRESS_ADD_INSN, "d,v,t",
		       reg, reg, mips_gp_register);
	  macro_build (ep, ADDRESS_LOAD_INSN, "t,o(b)",
		       reg, BFD_RELOC_MIPS_GOT_LO16, reg);
	  relax_switch ();
	  if (reg_needs_delay (mips_gp_register))
	    {
	      /* We need a nop before loading from $gp.  This special
		 check is required because the lui which starts the main
		 instruction stream does not refer to $gp, and so will not
		 insert the nop which may be required.  */
	      macro_build (NULL, "nop", "");
	    }
	  macro_build (ep, ADDRESS_LOAD_INSN, "t,o(b)", reg,
		       BFD_RELOC_MIPS_GOT16, mips_gp_register);
	  load_delay_nop ();
	  macro_build (ep, ADDRESS_ADDI_INSN, "t,r,j", reg, reg,
		       BFD_RELOC_LO16);
	  relax_end ();

	  if (ex.X_add_number != 0)
	    {
	      if (ex.X_add_number < -0x8000 || ex.X_add_number >= 0x8000)
		as_bad (_("PIC code offset overflow (max 16 signed bits)"));
	      ex.X_op = O_constant;
	      macro_build (&ex, ADDRESS_ADDI_INSN, "t,r,j", reg, reg,
			   BFD_RELOC_LO16);
	    }
	}
    }
  else
    abort ();

  if (mips_opts.noat && *used_at == 1)
    as_bad (_("Macro used $at after \".set noat\""));
}