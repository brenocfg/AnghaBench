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
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LABEL_REF ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_LABEL ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ USE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ computed_jump_p_1 (int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pc_rtx ; 

int
computed_jump_p (rtx insn)
{
  int i;
  if (JUMP_P (insn))
    {
      rtx pat = PATTERN (insn);

      if (find_reg_note (insn, REG_LABEL, NULL_RTX))
	return 0;
      else if (GET_CODE (pat) == PARALLEL)
	{
	  int len = XVECLEN (pat, 0);
	  int has_use_labelref = 0;

	  for (i = len - 1; i >= 0; i--)
	    if (GET_CODE (XVECEXP (pat, 0, i)) == USE
		&& (GET_CODE (XEXP (XVECEXP (pat, 0, i), 0))
		    == LABEL_REF))
	      has_use_labelref = 1;

	  if (! has_use_labelref)
	    for (i = len - 1; i >= 0; i--)
	      if (GET_CODE (XVECEXP (pat, 0, i)) == SET
		  && SET_DEST (XVECEXP (pat, 0, i)) == pc_rtx
		  && computed_jump_p_1 (SET_SRC (XVECEXP (pat, 0, i))))
		return 1;
	}
      else if (GET_CODE (pat) == SET
	       && SET_DEST (pat) == pc_rtx
	       && computed_jump_p_1 (SET_SRC (pat)))
	return 1;
    }
  return 0;
}