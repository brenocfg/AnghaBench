#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
typedef  TYPE_1__ expressionS ;
struct TYPE_8__ {scalar_t__ noat; } ;

/* Variables and functions */
 char const* ADDRESS_ADD_INSN ; 
 int AT ; 
 int BFD_RELOC_LO16 ; 
 scalar_t__ IS_SEXT_16BIT_NUM (scalar_t__) ; 
 int /*<<< orphan*/  IS_SEXT_32BIT_NUM (scalar_t__) ; 
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  macro_build (TYPE_1__*,char const*,char*,int,int,int) ; 
 int /*<<< orphan*/  macro_build_lui (TYPE_1__*,int) ; 
 TYPE_3__ mips_opts ; 
 int /*<<< orphan*/  normalize_constant_expr (TYPE_1__*) ; 

__attribute__((used)) static void
macro_build_ldst_constoffset (expressionS *ep, const char *op,
			      int treg, int breg, int dbl)
{
  assert (ep->X_op == O_constant);

  /* Sign-extending 32-bit constants makes their handling easier.  */
  if (!dbl)
    normalize_constant_expr (ep);

  /* Right now, this routine can only handle signed 32-bit constants.  */
  if (! IS_SEXT_32BIT_NUM(ep->X_add_number + 0x8000))
    as_warn (_("operand overflow"));

  if (IS_SEXT_16BIT_NUM(ep->X_add_number))
    {
      /* Signed 16-bit offset will fit in the op.  Easy!  */
      macro_build (ep, op, "t,o(b)", treg, BFD_RELOC_LO16, breg);
    }
  else
    {
      /* 32-bit offset, need multiple instructions and AT, like:
	   lui      $tempreg,const_hi       (BFD_RELOC_HI16_S)
	   addu     $tempreg,$tempreg,$breg
           <op>     $treg,const_lo($tempreg)   (BFD_RELOC_LO16)
         to handle the complete offset.  */
      macro_build_lui (ep, AT);
      macro_build (NULL, ADDRESS_ADD_INSN, "d,v,t", AT, AT, breg);
      macro_build (ep, op, "t,o(b)", treg, BFD_RELOC_LO16, AT);

      if (mips_opts.noat)
	as_bad (_("Macro used $at after \".set noat\""));
    }
}