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
 unsigned int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 size_t GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (size_t) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 unsigned int** hard_regno_nregs ; 

__attribute__((used)) static bool
covers_regno_no_parallel_p (rtx dest, unsigned int test_regno)
{
  unsigned int regno, endregno;

  if (GET_CODE (dest) == SUBREG
      && (((GET_MODE_SIZE (GET_MODE (dest))
	    + UNITS_PER_WORD - 1) / UNITS_PER_WORD)
	  == ((GET_MODE_SIZE (GET_MODE (SUBREG_REG (dest)))
	       + UNITS_PER_WORD - 1) / UNITS_PER_WORD)))
    dest = SUBREG_REG (dest);

  if (!REG_P (dest))
    return false;

  regno = REGNO (dest);
  endregno = (regno >= FIRST_PSEUDO_REGISTER ? regno + 1
	      : regno + hard_regno_nregs[regno][GET_MODE (dest)]);
  return (test_regno >= regno && test_regno < endregno);
}