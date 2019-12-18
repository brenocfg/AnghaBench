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
 scalar_t__ IF_THEN_ELSE ; 
 scalar_t__ LABEL_REF ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ PC ; 
 scalar_t__ RETURN ; 
 scalar_t__ SET ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 

int
condjump_p (rtx insn)
{
  rtx x = PATTERN (insn);

  if (GET_CODE (x) != SET
      || GET_CODE (SET_DEST (x)) != PC)
    return 0;

  x = SET_SRC (x);
  if (GET_CODE (x) == LABEL_REF)
    return 1;
  else
    return (GET_CODE (x) == IF_THEN_ELSE
	    && ((GET_CODE (XEXP (x, 2)) == PC
		 && (GET_CODE (XEXP (x, 1)) == LABEL_REF
		     || GET_CODE (XEXP (x, 1)) == RETURN))
		|| (GET_CODE (XEXP (x, 1)) == PC
		    && (GET_CODE (XEXP (x, 2)) == LABEL_REF
			|| GET_CODE (XEXP (x, 2)) == RETURN))));
}