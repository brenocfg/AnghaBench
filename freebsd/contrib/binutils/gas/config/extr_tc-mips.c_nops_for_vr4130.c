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
struct mips_cl_insn {TYPE_1__* insn_mo; int /*<<< orphan*/  noreorder_p; } ;
struct TYPE_4__ {scalar_t__ mips16; } ;
struct TYPE_3__ {int pinfo; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EXTRACT_OPERAND (int /*<<< orphan*/ ,struct mips_cl_insn const) ; 
 int INSN_WRITE_HI ; 
 int INSN_WRITE_LO ; 
 int MAX_VR4130_NOPS ; 
 scalar_t__ MF_HILO_INSN (int) ; 
 size_t MIPS16_EXTRACT_OPERAND (int /*<<< orphan*/ ,struct mips_cl_insn const) ; 
 int /*<<< orphan*/  MIPS_GR_REG ; 
 int /*<<< orphan*/  RD ; 
 int /*<<< orphan*/  RX ; 
 scalar_t__ insn_uses_reg (struct mips_cl_insn const*,int,int /*<<< orphan*/ ) ; 
 int* mips16_to_32_reg_map ; 
 TYPE_2__ mips_opts ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
nops_for_vr4130 (const struct mips_cl_insn *history,
		 const struct mips_cl_insn *insn)
{
  int i, j, reg;

  /* Check if the instruction writes to HI or LO.  MTHI and MTLO
     are not affected by the errata.  */
  if (insn != 0
      && ((insn->insn_mo->pinfo & (INSN_WRITE_HI | INSN_WRITE_LO)) == 0
	  || strcmp (insn->insn_mo->name, "mtlo") == 0
	  || strcmp (insn->insn_mo->name, "mthi") == 0))
    return 0;

  /* Search for the first MFLO or MFHI.  */
  for (i = 0; i < MAX_VR4130_NOPS; i++)
    if (!history[i].noreorder_p && MF_HILO_INSN (history[i].insn_mo->pinfo))
      {
	/* Extract the destination register.  */
	if (mips_opts.mips16)
	  reg = mips16_to_32_reg_map[MIPS16_EXTRACT_OPERAND (RX, history[i])];
	else
	  reg = EXTRACT_OPERAND (RD, history[i]);

	/* No nops are needed if INSN reads that register.  */
	if (insn != NULL && insn_uses_reg (insn, reg, MIPS_GR_REG))
	  return 0;

	/* ...or if any of the intervening instructions do.  */
	for (j = 0; j < i; j++)
	  if (insn_uses_reg (&history[j], reg, MIPS_GR_REG))
	    return 0;

	return MAX_VR4130_NOPS - i;
      }
  return 0;
}