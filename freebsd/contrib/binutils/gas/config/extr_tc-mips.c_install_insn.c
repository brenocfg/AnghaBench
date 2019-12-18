#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mips_cl_insn {int where; int insn_opcode; int extend; scalar_t__ use_extend; scalar_t__ mips16_absolute_jump_p; TYPE_1__* frag; } ;
struct TYPE_4__ {int /*<<< orphan*/  mips16; } ;
struct TYPE_3__ {char* fr_literal; } ;

/* Variables and functions */
 int /*<<< orphan*/  md_number_to_chars (char*,int,int) ; 
 TYPE_2__ mips_opts ; 

__attribute__((used)) static void
install_insn (const struct mips_cl_insn *insn)
{
  char *f = insn->frag->fr_literal + insn->where;
  if (!mips_opts.mips16)
    md_number_to_chars (f, insn->insn_opcode, 4);
  else if (insn->mips16_absolute_jump_p)
    {
      md_number_to_chars (f, insn->insn_opcode >> 16, 2);
      md_number_to_chars (f + 2, insn->insn_opcode & 0xffff, 2);
    }
  else
    {
      if (insn->use_extend)
	{
	  md_number_to_chars (f, 0xf000 | insn->extend, 2);
	  f += 2;
	}
      md_number_to_chars (f, insn->insn_opcode, 2);
    }
}