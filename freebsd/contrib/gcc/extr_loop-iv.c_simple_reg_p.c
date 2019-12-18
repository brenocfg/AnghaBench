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
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ HARD_REGISTER_NUM_P (unsigned int) ; 
 scalar_t__ MODE_INT ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subreg_lowpart_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
simple_reg_p (rtx reg)
{
  unsigned r;

  if (GET_CODE (reg) == SUBREG)
    {
      if (!subreg_lowpart_p (reg))
	return false;
      reg = SUBREG_REG (reg);
    }

  if (!REG_P (reg))
    return false;

  r = REGNO (reg);
  if (HARD_REGISTER_NUM_P (r))
    return false;

  if (GET_MODE_CLASS (GET_MODE (reg)) != MODE_INT)
    return false;

  return true;
}