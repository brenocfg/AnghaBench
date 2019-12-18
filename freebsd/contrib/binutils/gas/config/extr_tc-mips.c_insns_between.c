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
struct TYPE_4__ {int /*<<< orphan*/  mips16; } ;
struct TYPE_3__ {unsigned long pinfo; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_OPERAND (int /*<<< orphan*/ ,struct mips_cl_insn const) ; 
 int /*<<< orphan*/  FS ; 
 int /*<<< orphan*/  FT ; 
 scalar_t__ INSN2_USES_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long INSN_COP ; 
 unsigned long INSN_COPROC_MEMORY_DELAY ; 
 unsigned long INSN_COPROC_MOVE_DELAY ; 
 unsigned long INSN_LOAD_COPROC_DELAY ; 
 unsigned long INSN_LOAD_MEMORY_DELAY ; 
 unsigned long INSN_READ_COND_CODE ; 
 unsigned long INSN_READ_HI ; 
 unsigned long INSN_READ_LO ; 
 unsigned long INSN_WRITE_COND_CODE ; 
 unsigned long INSN_WRITE_FPR_S ; 
 unsigned long INSN_WRITE_FPR_T ; 
 unsigned long INSN_WRITE_GPR_T ; 
 unsigned long INSN_WRITE_HI ; 
 unsigned long INSN_WRITE_LO ; 
 scalar_t__ MF_HILO_INSN (unsigned long) ; 
 int /*<<< orphan*/  MIPS_FP_REG ; 
 int /*<<< orphan*/  MIPS_GR_REG ; 
 unsigned int NUM_FIX_VR4120_CLASSES ; 
 int /*<<< orphan*/  RD ; 
 int /*<<< orphan*/  RT ; 
 unsigned int classify_vr4120_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cop_interlocks ; 
 int /*<<< orphan*/  cop_mem_interlocks ; 
 int /*<<< orphan*/  gpr_interlocks ; 
 int /*<<< orphan*/  hilo_interlocks ; 
 int /*<<< orphan*/  know (unsigned long) ; 
 scalar_t__ mips_7000_hilo_fix ; 
 scalar_t__ mips_fix_vr4120 ; 
 TYPE_2__ mips_opts ; 
 int* vr4120_conflicts ; 

__attribute__((used)) static unsigned int
insns_between (const struct mips_cl_insn *insn1,
	       const struct mips_cl_insn *insn2)
{
  unsigned long pinfo1, pinfo2;

  /* This function needs to know which pinfo flags are set for INSN2
     and which registers INSN2 uses.  The former is stored in PINFO2 and
     the latter is tested via INSN2_USES_REG.  If INSN2 is null, PINFO2
     will have every flag set and INSN2_USES_REG will always return true.  */
  pinfo1 = insn1->insn_mo->pinfo;
  pinfo2 = insn2 ? insn2->insn_mo->pinfo : ~0U;

#define INSN2_USES_REG(REG, CLASS) \
   (insn2 == NULL || insn_uses_reg (insn2, REG, CLASS))

  /* For most targets, write-after-read dependencies on the HI and LO
     registers must be separated by at least two instructions.  */
  if (!hilo_interlocks)
    {
      if ((pinfo1 & INSN_READ_LO) && (pinfo2 & INSN_WRITE_LO))
	return 2;
      if ((pinfo1 & INSN_READ_HI) && (pinfo2 & INSN_WRITE_HI))
	return 2;
    }

  /* If we're working around r7000 errata, there must be two instructions
     between an mfhi or mflo and any instruction that uses the result.  */
  if (mips_7000_hilo_fix
      && MF_HILO_INSN (pinfo1)
      && INSN2_USES_REG (EXTRACT_OPERAND (RD, *insn1), MIPS_GR_REG))
    return 2;

  /* If working around VR4120 errata, check for combinations that need
     a single intervening instruction.  */
  if (mips_fix_vr4120)
    {
      unsigned int class1, class2;

      class1 = classify_vr4120_insn (insn1->insn_mo->name);
      if (class1 != NUM_FIX_VR4120_CLASSES && vr4120_conflicts[class1] != 0)
	{
	  if (insn2 == NULL)
	    return 1;
	  class2 = classify_vr4120_insn (insn2->insn_mo->name);
	  if (vr4120_conflicts[class1] & (1 << class2))
	    return 1;
	}
    }

  if (!mips_opts.mips16)
    {
      /* Check for GPR or coprocessor load delays.  All such delays
	 are on the RT register.  */
      /* Itbl support may require additional care here.  */
      if ((!gpr_interlocks && (pinfo1 & INSN_LOAD_MEMORY_DELAY))
	  || (!cop_interlocks && (pinfo1 & INSN_LOAD_COPROC_DELAY)))
	{
	  know (pinfo1 & INSN_WRITE_GPR_T);
	  if (INSN2_USES_REG (EXTRACT_OPERAND (RT, *insn1), MIPS_GR_REG))
	    return 1;
	}

      /* Check for generic coprocessor hazards.

	 This case is not handled very well.  There is no special
	 knowledge of CP0 handling, and the coprocessors other than
	 the floating point unit are not distinguished at all.  */
      /* Itbl support may require additional care here. FIXME!
	 Need to modify this to include knowledge about
	 user specified delays!  */
      else if ((!cop_interlocks && (pinfo1 & INSN_COPROC_MOVE_DELAY))
	       || (!cop_mem_interlocks && (pinfo1 & INSN_COPROC_MEMORY_DELAY)))
	{
	  /* Handle cases where INSN1 writes to a known general coprocessor
	     register.  There must be a one instruction delay before INSN2
	     if INSN2 reads that register, otherwise no delay is needed.  */
	  if (pinfo1 & INSN_WRITE_FPR_T)
	    {
	      if (INSN2_USES_REG (EXTRACT_OPERAND (FT, *insn1), MIPS_FP_REG))
		return 1;
	    }
	  else if (pinfo1 & INSN_WRITE_FPR_S)
	    {
	      if (INSN2_USES_REG (EXTRACT_OPERAND (FS, *insn1), MIPS_FP_REG))
		return 1;
	    }
	  else
	    {
	      /* Read-after-write dependencies on the control registers
		 require a two-instruction gap.  */
	      if ((pinfo1 & INSN_WRITE_COND_CODE)
		  && (pinfo2 & INSN_READ_COND_CODE))
		return 2;

	      /* We don't know exactly what INSN1 does.  If INSN2 is
		 also a coprocessor instruction, assume there must be
		 a one instruction gap.  */
	      if (pinfo2 & INSN_COP)
		return 1;
	    }
	}

      /* Check for read-after-write dependencies on the coprocessor
	 control registers in cases where INSN1 does not need a general
	 coprocessor delay.  This means that INSN1 is a floating point
	 comparison instruction.  */
      /* Itbl support may require additional care here.  */
      else if (!cop_interlocks
	       && (pinfo1 & INSN_WRITE_COND_CODE)
	       && (pinfo2 & INSN_READ_COND_CODE))
	return 1;
    }

#undef INSN2_USES_REG

  return 0;
}