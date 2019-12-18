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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARISON_P (int /*<<< orphan*/ ) ; 
 int CR0_REGNO ; 
 scalar_t__ CR_REGNO_P (int) ; 
#define  EQ 141 
#define  GE 140 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
#define  GEU 139 
#define  GT 138 
#define  GTU 137 
#define  LE 136 
#define  LEU 135 
#define  LT 134 
#define  LTU 133 
#define  NE 132 
#define  ORDERED 131 
 scalar_t__ REG ; 
 int REGNO (int /*<<< orphan*/ ) ; 
#define  UNGE 130 
#define  UNLE 129 
#define  UNORDERED 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  validate_condition_mode (int,int) ; 

int
ccr_bit (rtx op, int scc_p)
{
  enum rtx_code code = GET_CODE (op);
  enum machine_mode cc_mode;
  int cc_regnum;
  int base_bit;
  rtx reg;

  if (!COMPARISON_P (op))
    return -1;

  reg = XEXP (op, 0);

  gcc_assert (GET_CODE (reg) == REG && CR_REGNO_P (REGNO (reg)));

  cc_mode = GET_MODE (reg);
  cc_regnum = REGNO (reg);
  base_bit = 4 * (cc_regnum - CR0_REGNO);

  validate_condition_mode (code, cc_mode);

  /* When generating a sCOND operation, only positive conditions are
     allowed.  */
  gcc_assert (!scc_p
	      || code == EQ || code == GT || code == LT || code == UNORDERED
	      || code == GTU || code == LTU);

  switch (code)
    {
    case NE:
      return scc_p ? base_bit + 3 : base_bit + 2;
    case EQ:
      return base_bit + 2;
    case GT:  case GTU:  case UNLE:
      return base_bit + 1;
    case LT:  case LTU:  case UNGE:
      return base_bit;
    case ORDERED:  case UNORDERED:
      return base_bit + 3;

    case GE:  case GEU:
      /* If scc, we will have done a cror to put the bit in the
	 unordered position.  So test that bit.  For integer, this is ! LT
	 unless this is an scc insn.  */
      return scc_p ? base_bit + 3 : base_bit;

    case LE:  case LEU:
      return scc_p ? base_bit + 3 : base_bit + 1;

    default:
      gcc_unreachable ();
    }
}