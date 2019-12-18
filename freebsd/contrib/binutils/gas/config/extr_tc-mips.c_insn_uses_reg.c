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
struct mips_cl_insn {TYPE_1__* insn_mo; } ;
typedef  enum mips_regclass { ____Placeholder_mips_regclass } mips_regclass ;
struct TYPE_4__ {int mips16; } ;
struct TYPE_3__ {int pinfo; } ;

/* Variables and functions */
 unsigned int EXTRACT_OPERAND (int /*<<< orphan*/ ,struct mips_cl_insn const) ; 
 int /*<<< orphan*/  FS ; 
 int /*<<< orphan*/  FT ; 
 int INSN_READ_FPR_S ; 
 int INSN_READ_FPR_T ; 
 int INSN_READ_GPR_S ; 
 int INSN_READ_GPR_T ; 
 unsigned int MIPS16_EXTRACT_OPERAND (int /*<<< orphan*/ ,struct mips_cl_insn const) ; 
 int MIPS16_INSN_READ_31 ; 
 int MIPS16_INSN_READ_GPR_X ; 
 int MIPS16_INSN_READ_SP ; 
 int MIPS16_INSN_READ_T ; 
 int MIPS16_INSN_READ_X ; 
 int MIPS16_INSN_READ_Y ; 
 int MIPS16_INSN_READ_Z ; 
 int MIPS16_REG ; 
 int MIPS_FP_REG ; 
 int MIPS_GR_REG ; 
 int /*<<< orphan*/  MOVE32Z ; 
 unsigned int RA ; 
 int /*<<< orphan*/  REGR32 ; 
 int /*<<< orphan*/  RS ; 
 int /*<<< orphan*/  RT ; 
 int /*<<< orphan*/  RX ; 
 int /*<<< orphan*/  RY ; 
 unsigned int SP ; 
 unsigned int TREG ; 
 unsigned int ZERO ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int* mips16_to_32_reg_map ; 
 TYPE_2__ mips_opts ; 

__attribute__((used)) static int
insn_uses_reg (const struct mips_cl_insn *ip, unsigned int reg,
	       enum mips_regclass class)
{
  if (class == MIPS16_REG)
    {
      assert (mips_opts.mips16);
      reg = mips16_to_32_reg_map[reg];
      class = MIPS_GR_REG;
    }

  /* Don't report on general register ZERO, since it never changes.  */
  if (class == MIPS_GR_REG && reg == ZERO)
    return 0;

  if (class == MIPS_FP_REG)
    {
      assert (! mips_opts.mips16);
      /* If we are called with either $f0 or $f1, we must check $f0.
	 This is not optimal, because it will introduce an unnecessary
	 NOP between "lwc1 $f0" and "swc1 $f1".  To fix this we would
	 need to distinguish reading both $f0 and $f1 or just one of
	 them.  Note that we don't have to check the other way,
	 because there is no instruction that sets both $f0 and $f1
	 and requires a delay.  */
      if ((ip->insn_mo->pinfo & INSN_READ_FPR_S)
	  && ((EXTRACT_OPERAND (FS, *ip) & ~(unsigned) 1)
	      == (reg &~ (unsigned) 1)))
	return 1;
      if ((ip->insn_mo->pinfo & INSN_READ_FPR_T)
	  && ((EXTRACT_OPERAND (FT, *ip) & ~(unsigned) 1)
	      == (reg &~ (unsigned) 1)))
	return 1;
    }
  else if (! mips_opts.mips16)
    {
      if ((ip->insn_mo->pinfo & INSN_READ_GPR_S)
	  && EXTRACT_OPERAND (RS, *ip) == reg)
	return 1;
      if ((ip->insn_mo->pinfo & INSN_READ_GPR_T)
	  && EXTRACT_OPERAND (RT, *ip) == reg)
	return 1;
    }
  else
    {
      if ((ip->insn_mo->pinfo & MIPS16_INSN_READ_X)
	  && mips16_to_32_reg_map[MIPS16_EXTRACT_OPERAND (RX, *ip)] == reg)
	return 1;
      if ((ip->insn_mo->pinfo & MIPS16_INSN_READ_Y)
	  && mips16_to_32_reg_map[MIPS16_EXTRACT_OPERAND (RY, *ip)] == reg)
	return 1;
      if ((ip->insn_mo->pinfo & MIPS16_INSN_READ_Z)
	  && (mips16_to_32_reg_map[MIPS16_EXTRACT_OPERAND (MOVE32Z, *ip)]
	      == reg))
	return 1;
      if ((ip->insn_mo->pinfo & MIPS16_INSN_READ_T) && reg == TREG)
	return 1;
      if ((ip->insn_mo->pinfo & MIPS16_INSN_READ_SP) && reg == SP)
	return 1;
      if ((ip->insn_mo->pinfo & MIPS16_INSN_READ_31) && reg == RA)
	return 1;
      if ((ip->insn_mo->pinfo & MIPS16_INSN_READ_GPR_X)
	  && MIPS16_EXTRACT_OPERAND (REGR32, *ip) == reg)
	return 1;
    }

  return 0;
}