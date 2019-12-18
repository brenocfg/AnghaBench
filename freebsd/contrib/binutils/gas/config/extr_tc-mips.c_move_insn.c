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
struct mips_cl_insn {long where; TYPE_1__** fixp; int /*<<< orphan*/ * frag; } ;
typedef  int /*<<< orphan*/  fragS ;
struct TYPE_2__ {long fx_where; int /*<<< orphan*/ * fx_frag; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__**) ; 
 int /*<<< orphan*/  install_insn (struct mips_cl_insn*) ; 

__attribute__((used)) static void
move_insn (struct mips_cl_insn *insn, fragS *frag, long where)
{
  size_t i;

  insn->frag = frag;
  insn->where = where;
  for (i = 0; i < ARRAY_SIZE (insn->fixp); i++)
    if (insn->fixp[i] != NULL)
      {
	insn->fixp[i]->fx_frag = frag;
	insn->fixp[i]->fx_where = where;
      }
  install_insn (insn);
}