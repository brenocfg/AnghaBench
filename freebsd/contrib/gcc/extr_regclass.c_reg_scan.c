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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TV_REG_SCAN ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allocate_reg_info (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max_parallel ; 
 scalar_t__ max_set_parallel ; 
 int /*<<< orphan*/  reg_scan_mark_refs (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
reg_scan (rtx f, unsigned int nregs)
{
  rtx insn;

  timevar_push (TV_REG_SCAN);

  allocate_reg_info (nregs, TRUE, FALSE);
  max_parallel = 3;
  max_set_parallel = 0;

  for (insn = f; insn; insn = NEXT_INSN (insn))
    if (INSN_P (insn))
      {
	rtx pat = PATTERN (insn);
	if (GET_CODE (pat) == PARALLEL
	    && XVECLEN (pat, 0) > max_parallel)
	  max_parallel = XVECLEN (pat, 0);
	reg_scan_mark_refs (pat, insn, 0);

	if (REG_NOTES (insn))
	  reg_scan_mark_refs (REG_NOTES (insn), insn, 1);
      }

  max_parallel += max_set_parallel;

  timevar_pop (TV_REG_SCAN);
}