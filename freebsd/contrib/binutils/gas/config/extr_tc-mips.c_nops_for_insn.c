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
struct mips_cl_insn {int /*<<< orphan*/  noreorder_p; } ;

/* Variables and functions */
 int MAX_DELAY_NOPS ; 
 int insns_between (struct mips_cl_insn const*,struct mips_cl_insn const*) ; 
 scalar_t__ mips_fix_vr4130 ; 
 int nops_for_vr4130 (struct mips_cl_insn const*,struct mips_cl_insn const*) ; 

__attribute__((used)) static int
nops_for_insn (const struct mips_cl_insn *history,
	       const struct mips_cl_insn *insn)
{
  int i, nops, tmp_nops;

  nops = 0;
  for (i = 0; i < MAX_DELAY_NOPS; i++)
    if (!history[i].noreorder_p)
      {
	tmp_nops = insns_between (history + i, insn) - i;
	if (tmp_nops > nops)
	  nops = tmp_nops;
      }

  if (mips_fix_vr4130)
    {
      tmp_nops = nops_for_vr4130 (history, insn);
      if (tmp_nops > nops)
	nops = tmp_nops;
    }

  return nops;
}