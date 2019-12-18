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
struct value_data {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 unsigned int** hard_regno_nregs ; 
 int /*<<< orphan*/  kill_value_regno (unsigned int,unsigned int,struct value_data*) ; 
 int /*<<< orphan*/  simplify_subreg (size_t,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kill_value (rtx x, struct value_data *vd)
{
  rtx orig_rtx = x;

  if (GET_CODE (x) == SUBREG)
    {
      x = simplify_subreg (GET_MODE (x), SUBREG_REG (x),
			   GET_MODE (SUBREG_REG (x)), SUBREG_BYTE (x));
      if (x == NULL_RTX)
	x = SUBREG_REG (orig_rtx);
    }
  if (REG_P (x))
    {
      unsigned int regno = REGNO (x);
      unsigned int n = hard_regno_nregs[regno][GET_MODE (x)];

      kill_value_regno (regno, n, vd);
    }
}