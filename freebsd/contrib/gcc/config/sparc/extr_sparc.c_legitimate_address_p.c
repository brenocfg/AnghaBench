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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTANT_P (int /*<<< orphan*/ *) ; 
 scalar_t__ CONST_INT ; 
 int DFmode ; 
 int DImode ; 
 int FIRST_PSEUDO_REGISTER ; 
 int FRAME_POINTER_REGNUM ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ LO_SUM ; 
 scalar_t__ MEM ; 
 scalar_t__ PLUS ; 
 int Pmode ; 
 int REGNO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REGNO_OK_FOR_BASE_P (int) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ *) ; 
 scalar_t__ RTX_OK_FOR_OFFSET_P (int /*<<< orphan*/ *) ; 
 scalar_t__ RTX_OK_FOR_OLO10_P (int /*<<< orphan*/ *) ; 
 scalar_t__ SMALL_INT (int /*<<< orphan*/ *) ; 
 scalar_t__ SPARC_SYMBOL_REF_TLS_P (int /*<<< orphan*/ *) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/ * SUBREG_REG (int /*<<< orphan*/ *) ; 
 scalar_t__ TARGET_ARCH32 ; 
 scalar_t__ TARGET_ARCH64 ; 
 int /*<<< orphan*/  TARGET_CM_MEDMID ; 
 scalar_t__ TARGET_FPU ; 
 scalar_t__ TARGET_HARD_QUAD ; 
 int TFmode ; 
 scalar_t__ USE_AS_OFFSETABLE_LO10 ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 int flag_pic ; 
 int /*<<< orphan*/  optimize ; 
 int /*<<< orphan*/ * pic_offset_table_rtx ; 
 int /*<<< orphan*/  symbolic_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
legitimate_address_p (enum machine_mode mode, rtx addr, int strict)
{
  rtx rs1 = NULL, rs2 = NULL, imm1 = NULL;

  if (REG_P (addr) || GET_CODE (addr) == SUBREG)
    rs1 = addr;
  else if (GET_CODE (addr) == PLUS)
    {
      rs1 = XEXP (addr, 0);
      rs2 = XEXP (addr, 1);

      /* Canonicalize.  REG comes first, if there are no regs,
	 LO_SUM comes first.  */
      if (!REG_P (rs1)
	  && GET_CODE (rs1) != SUBREG
	  && (REG_P (rs2)
	      || GET_CODE (rs2) == SUBREG
	      || (GET_CODE (rs2) == LO_SUM && GET_CODE (rs1) != LO_SUM)))
	{
	  rs1 = XEXP (addr, 1);
	  rs2 = XEXP (addr, 0);
	}

      if ((flag_pic == 1
	   && rs1 == pic_offset_table_rtx
	   && !REG_P (rs2)
	   && GET_CODE (rs2) != SUBREG
	   && GET_CODE (rs2) != LO_SUM
	   && GET_CODE (rs2) != MEM
	   && ! SPARC_SYMBOL_REF_TLS_P (rs2)
	   && (! symbolic_operand (rs2, VOIDmode) || mode == Pmode)
	   && (GET_CODE (rs2) != CONST_INT || SMALL_INT (rs2)))
	  || ((REG_P (rs1)
	       || GET_CODE (rs1) == SUBREG)
	      && RTX_OK_FOR_OFFSET_P (rs2)))
	{
	  imm1 = rs2;
	  rs2 = NULL;
	}
      else if ((REG_P (rs1) || GET_CODE (rs1) == SUBREG)
	       && (REG_P (rs2) || GET_CODE (rs2) == SUBREG))
	{
	  /* We prohibit REG + REG for TFmode when there are no quad move insns
	     and we consequently need to split.  We do this because REG+REG
	     is not an offsettable address.  If we get the situation in reload
	     where source and destination of a movtf pattern are both MEMs with
	     REG+REG address, then only one of them gets converted to an
	     offsettable address.  */
	  if (mode == TFmode
	      && ! (TARGET_FPU && TARGET_ARCH64 && TARGET_HARD_QUAD))
	    return 0;

	  /* We prohibit REG + REG on ARCH32 if not optimizing for
	     DFmode/DImode because then mem_min_alignment is likely to be zero
	     after reload and the  forced split would lack a matching splitter
	     pattern.  */
	  if (TARGET_ARCH32 && !optimize
	      && (mode == DFmode || mode == DImode))
	    return 0;
	}
      else if (USE_AS_OFFSETABLE_LO10
	       && GET_CODE (rs1) == LO_SUM
	       && TARGET_ARCH64
	       && ! TARGET_CM_MEDMID
	       && RTX_OK_FOR_OLO10_P (rs2))
	{
	  rs2 = NULL;
	  imm1 = XEXP (rs1, 1);
	  rs1 = XEXP (rs1, 0);
	  if (! CONSTANT_P (imm1) || SPARC_SYMBOL_REF_TLS_P (rs1))
	    return 0;
	}
    }
  else if (GET_CODE (addr) == LO_SUM)
    {
      rs1 = XEXP (addr, 0);
      imm1 = XEXP (addr, 1);

      if (! CONSTANT_P (imm1) || SPARC_SYMBOL_REF_TLS_P (rs1))
	return 0;

      /* We can't allow TFmode in 32-bit mode, because an offset greater
	 than the alignment (8) may cause the LO_SUM to overflow.  */
      if (mode == TFmode && TARGET_ARCH32)
	return 0;
    }
  else if (GET_CODE (addr) == CONST_INT && SMALL_INT (addr))
    return 1;
  else
    return 0;

  if (GET_CODE (rs1) == SUBREG)
    rs1 = SUBREG_REG (rs1);
  if (!REG_P (rs1))
    return 0;

  if (rs2)
    {
      if (GET_CODE (rs2) == SUBREG)
	rs2 = SUBREG_REG (rs2);
      if (!REG_P (rs2))
	return 0;
    }

  if (strict)
    {
      if (!REGNO_OK_FOR_BASE_P (REGNO (rs1))
	  || (rs2 && !REGNO_OK_FOR_BASE_P (REGNO (rs2))))
	return 0;
    }
  else
    {
      if ((REGNO (rs1) >= 32
	   && REGNO (rs1) != FRAME_POINTER_REGNUM
	   && REGNO (rs1) < FIRST_PSEUDO_REGISTER)
	  || (rs2
	      && (REGNO (rs2) >= 32
		  && REGNO (rs2) != FRAME_POINTER_REGNUM
		  && REGNO (rs2) < FIRST_PSEUDO_REGISTER)))
	return 0;
    }
  return 1;
}