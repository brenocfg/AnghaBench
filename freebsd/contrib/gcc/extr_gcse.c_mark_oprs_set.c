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
 scalar_t__ CALL ; 
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_call (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_clobber (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_oprs_set (rtx insn)
{
  rtx pat = PATTERN (insn);
  int i;

  if (GET_CODE (pat) == SET)
    mark_set (pat, insn);
  else if (GET_CODE (pat) == PARALLEL)
    for (i = 0; i < XVECLEN (pat, 0); i++)
      {
	rtx x = XVECEXP (pat, 0, i);

	if (GET_CODE (x) == SET)
	  mark_set (x, insn);
	else if (GET_CODE (x) == CLOBBER)
	  mark_clobber (x, insn);
	else if (GET_CODE (x) == CALL)
	  mark_call (insn);
      }

  else if (GET_CODE (pat) == CLOBBER)
    mark_clobber (pat, insn);
  else if (GET_CODE (pat) == CALL)
    mark_call (insn);
}