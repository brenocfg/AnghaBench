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
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NONJUMP_INSN_P (int /*<<< orphan*/ ) ; 
 int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  all_btrs ; 
 int /*<<< orphan*/  btr_referenced_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
insn_sets_btr_p (rtx insn, int check_const, int *regno)
{
  rtx set;

  if (NONJUMP_INSN_P (insn)
      && (set = single_set (insn)))
    {
      rtx dest = SET_DEST (set);
      rtx src = SET_SRC (set);

      if (GET_CODE (dest) == SUBREG)
	dest = XEXP (dest, 0);

      if (REG_P (dest)
	  && TEST_HARD_REG_BIT (all_btrs, REGNO (dest)))
	{
	  gcc_assert (!btr_referenced_p (src, NULL));

	  if (!check_const || CONSTANT_P (src))
	    {
	      if (regno)
		*regno = REGNO (dest);
	      return 1;
	    }
	}
    }
  return 0;
}