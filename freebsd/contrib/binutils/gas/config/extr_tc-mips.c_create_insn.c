#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mips_opcode {int /*<<< orphan*/  match; } ;
struct mips_cl_insn {int fixed_p; int noreorder_p; scalar_t__ mips16_absolute_jump_p; int /*<<< orphan*/ ** fixp; scalar_t__ where; int /*<<< orphan*/ * frag; int /*<<< orphan*/  insn_opcode; scalar_t__ extend; int /*<<< orphan*/  use_extend; struct mips_opcode const* insn_mo; } ;
struct TYPE_2__ {scalar_t__ noreorder; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ mips_opts ; 

__attribute__((used)) static void
create_insn (struct mips_cl_insn *insn, const struct mips_opcode *mo)
{
  size_t i;

  insn->insn_mo = mo;
  insn->use_extend = FALSE;
  insn->extend = 0;
  insn->insn_opcode = mo->match;
  insn->frag = NULL;
  insn->where = 0;
  for (i = 0; i < ARRAY_SIZE (insn->fixp); i++)
    insn->fixp[i] = NULL;
  insn->fixed_p = (mips_opts.noreorder > 0);
  insn->noreorder_p = (mips_opts.noreorder > 0);
  insn->mips16_absolute_jump_p = 0;
}