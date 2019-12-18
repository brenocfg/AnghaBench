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
struct likely_spilled_retval_info {unsigned int regno; unsigned int nregs; unsigned int mask; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ BB_END (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_LIKELY_SPILLED_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUNCTION_VALUE_REGNO_P (unsigned int) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  NONJUMP_INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  PATTERN (scalar_t__) ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 unsigned int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REGNO_REG_CLASS (unsigned int) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ USE ; 
 scalar_t__ XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int** hard_regno_nregs ; 
 int /*<<< orphan*/  likely_spilled_retval_1 ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct likely_spilled_retval_info*) ; 
 int /*<<< orphan*/  this_basic_block ; 

__attribute__((used)) static int
likely_spilled_retval_p (rtx insn)
{
  rtx use = BB_END (this_basic_block);
  rtx reg, p;
  unsigned regno, nregs;
  /* We assume here that no machine mode needs more than
     32 hard registers when the value overlaps with a register
     for which FUNCTION_VALUE_REGNO_P is true.  */
  unsigned mask;
  struct likely_spilled_retval_info info;

  if (!NONJUMP_INSN_P (use) || GET_CODE (PATTERN (use)) != USE || insn == use)
    return 0;
  reg = XEXP (PATTERN (use), 0);
  if (!REG_P (reg) || !FUNCTION_VALUE_REGNO_P (REGNO (reg)))
    return 0;
  regno = REGNO (reg);
  nregs = hard_regno_nregs[regno][GET_MODE (reg)];
  if (nregs == 1)
    return 0;
  mask = (2U << (nregs - 1)) - 1;

  /* Disregard parts of the return value that are set later.  */
  info.regno = regno;
  info.nregs = nregs;
  info.mask = mask;
  for (p = PREV_INSN (use); info.mask && p != insn; p = PREV_INSN (p))
    note_stores (PATTERN (insn), likely_spilled_retval_1, &info);
  mask = info.mask;

  /* Check if any of the (probably) live return value registers is
     likely spilled.  */
  nregs --;
  do
    {
      if ((mask & 1 << nregs)
	  && CLASS_LIKELY_SPILLED_P (REGNO_REG_CLASS (regno + nregs)))
	return 1;
    } while (nregs--);
  return 0;
}