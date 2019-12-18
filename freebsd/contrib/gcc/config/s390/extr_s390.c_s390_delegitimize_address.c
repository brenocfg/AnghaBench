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
 scalar_t__ CONST ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 scalar_t__ PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_GOT ; 
 scalar_t__ UNSPEC_GOTENT ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
s390_delegitimize_address (rtx orig_x)
{
  rtx x = orig_x, y;

  if (GET_CODE (x) != MEM)
    return orig_x;

  x = XEXP (x, 0);
  if (GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 1)) == CONST
      && GET_CODE (XEXP (x, 0)) == REG
      && REGNO (XEXP (x, 0)) == PIC_OFFSET_TABLE_REGNUM)
    {
      y = XEXP (XEXP (x, 1), 0);
      if (GET_CODE (y) == UNSPEC
	  && XINT (y, 1) == UNSPEC_GOT)
	return XVECEXP (y, 0, 0);
      return orig_x;
    }

  if (GET_CODE (x) == CONST)
    {
      y = XEXP (x, 0);
      if (GET_CODE (y) == UNSPEC
	  && XINT (y, 1) == UNSPEC_GOTENT)
	return XVECEXP (y, 0, 0);
      return orig_x;
    }

  return orig_x;
}