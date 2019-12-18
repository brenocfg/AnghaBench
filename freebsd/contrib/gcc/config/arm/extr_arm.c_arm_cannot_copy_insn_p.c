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
 int FALSE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_PIC_BASE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
arm_cannot_copy_insn_p (rtx insn)
{
  rtx pat = PATTERN (insn);

  if (GET_CODE (pat) == PARALLEL
      && GET_CODE (XVECEXP (pat, 0, 0)) == SET)
    {
      rtx rhs = SET_SRC (XVECEXP (pat, 0, 0));

      if (GET_CODE (rhs) == UNSPEC
	  && XINT (rhs, 1) == UNSPEC_PIC_BASE)
	return TRUE;

      if (GET_CODE (rhs) == MEM
	  && GET_CODE (XEXP (rhs, 0)) == UNSPEC
	  && XINT (XEXP (rhs, 0), 1) == UNSPEC_PIC_BASE)
	return TRUE;
    }

  return FALSE;
}