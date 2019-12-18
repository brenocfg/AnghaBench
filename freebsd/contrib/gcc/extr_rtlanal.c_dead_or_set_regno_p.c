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
 scalar_t__ CALL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ COND_EXEC ; 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DEAD ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int covers_regno_p (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ find_regno_fusage (int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 scalar_t__ find_regno_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int
dead_or_set_regno_p (rtx insn, unsigned int test_regno)
{
  rtx pattern;

  /* See if there is a death note for something that includes TEST_REGNO.  */
  if (find_regno_note (insn, REG_DEAD, test_regno))
    return 1;

  if (CALL_P (insn)
      && find_regno_fusage (insn, CLOBBER, test_regno))
    return 1;

  pattern = PATTERN (insn);

  if (GET_CODE (pattern) == COND_EXEC)
    pattern = COND_EXEC_CODE (pattern);

  if (GET_CODE (pattern) == SET)
    return covers_regno_p (SET_DEST (pattern), test_regno);
  else if (GET_CODE (pattern) == PARALLEL)
    {
      int i;

      for (i = XVECLEN (pattern, 0) - 1; i >= 0; i--)
	{
	  rtx body = XVECEXP (pattern, 0, i);

	  if (GET_CODE (body) == COND_EXEC)
	    body = COND_EXEC_CODE (body);

	  if ((GET_CODE (body) == SET || GET_CODE (body) == CLOBBER)
	      && covers_regno_p (SET_DEST (body), test_regno))
	    return 1;
	}
    }

  return 0;
}