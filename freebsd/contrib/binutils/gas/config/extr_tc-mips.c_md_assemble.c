#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mips_cl_insn {TYPE_1__* insn_mo; int /*<<< orphan*/  insn_opcode; } ;
typedef  int /*<<< orphan*/  bfd_reloc_code_real_type ;
struct TYPE_10__ {scalar_t__ X_op; } ;
struct TYPE_9__ {scalar_t__ mips16; } ;
struct TYPE_8__ {scalar_t__ X_op; } ;
struct TYPE_7__ {scalar_t__ pinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_UNUSED ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_MACRO ; 
 scalar_t__ O_absent ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  append_insn (struct mips_cl_insn*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  as_bad (char*,scalar_t__,char*) ; 
 TYPE_5__ imm2_expr ; 
 TYPE_2__ imm_expr ; 
 int /*<<< orphan*/ * imm_reloc ; 
 scalar_t__ insn_error ; 
 int /*<<< orphan*/  macro (struct mips_cl_insn*) ; 
 int /*<<< orphan*/  macro_end () ; 
 int /*<<< orphan*/  macro_start () ; 
 int /*<<< orphan*/  mips16_ip (char*,struct mips_cl_insn*) ; 
 int /*<<< orphan*/  mips16_macro (struct mips_cl_insn*) ; 
 int /*<<< orphan*/  mips_ip (char*,struct mips_cl_insn*) ; 
 TYPE_3__ mips_opts ; 
 TYPE_2__ offset_expr ; 
 int /*<<< orphan*/ * offset_reloc ; 

void
md_assemble (char *str)
{
  struct mips_cl_insn insn;
  bfd_reloc_code_real_type unused_reloc[3]
    = {BFD_RELOC_UNUSED, BFD_RELOC_UNUSED, BFD_RELOC_UNUSED};

  imm_expr.X_op = O_absent;
  imm2_expr.X_op = O_absent;
  offset_expr.X_op = O_absent;
  imm_reloc[0] = BFD_RELOC_UNUSED;
  imm_reloc[1] = BFD_RELOC_UNUSED;
  imm_reloc[2] = BFD_RELOC_UNUSED;
  offset_reloc[0] = BFD_RELOC_UNUSED;
  offset_reloc[1] = BFD_RELOC_UNUSED;
  offset_reloc[2] = BFD_RELOC_UNUSED;

  if (mips_opts.mips16)
    mips16_ip (str, &insn);
  else
    {
      mips_ip (str, &insn);
      DBG ((_("returned from mips_ip(%s) insn_opcode = 0x%x\n"),
	    str, insn.insn_opcode));
    }

  if (insn_error)
    {
      as_bad ("%s `%s'", insn_error, str);
      return;
    }

  if (insn.insn_mo->pinfo == INSN_MACRO)
    {
      macro_start ();
      if (mips_opts.mips16)
	mips16_macro (&insn);
      else
	macro (&insn);
      macro_end ();
    }
  else
    {
      if (imm_expr.X_op != O_absent)
	append_insn (&insn, &imm_expr, imm_reloc);
      else if (offset_expr.X_op != O_absent)
	append_insn (&insn, &offset_expr, offset_reloc);
      else
	append_insn (&insn, NULL, unused_reloc);
    }
}