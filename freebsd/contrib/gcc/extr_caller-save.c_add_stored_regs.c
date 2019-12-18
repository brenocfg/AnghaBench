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
typedef  int /*<<< orphan*/  regset ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CLOBBER ; 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int** hard_regno_nregs ; 
 int subreg_regno_offset (int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
add_stored_regs (rtx reg, rtx setter, void *data)
{
  int regno, endregno, i;
  enum machine_mode mode = GET_MODE (reg);
  int offset = 0;

  if (GET_CODE (setter) == CLOBBER)
    return;

  if (GET_CODE (reg) == SUBREG && REG_P (SUBREG_REG (reg)))
    {
      offset = subreg_regno_offset (REGNO (SUBREG_REG (reg)),
				    GET_MODE (SUBREG_REG (reg)),
				    SUBREG_BYTE (reg),
				    GET_MODE (reg));
      reg = SUBREG_REG (reg);
    }

  if (!REG_P (reg) || REGNO (reg) >= FIRST_PSEUDO_REGISTER)
    return;

  regno = REGNO (reg) + offset;
  endregno = regno + hard_regno_nregs[regno][mode];

  for (i = regno; i < endregno; i++)
    SET_REGNO_REG_SET ((regset) data, i);
}