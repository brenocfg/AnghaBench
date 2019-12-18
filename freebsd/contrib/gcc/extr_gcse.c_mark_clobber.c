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

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ STRICT_LOW_PART ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_last_mem_set_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_set_bitmap ; 

__attribute__((used)) static void
mark_clobber (rtx pat, rtx insn)
{
  rtx clob = XEXP (pat, 0);

  while (GET_CODE (clob) == SUBREG || GET_CODE (clob) == STRICT_LOW_PART)
    clob = XEXP (clob, 0);

  if (REG_P (clob))
    SET_REGNO_REG_SET (reg_set_bitmap, REGNO (clob));
  else
    record_last_mem_set_info (insn);
}