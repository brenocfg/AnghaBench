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
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPEC_GOT ; 
 scalar_t__ UNSPEC_GOTNTPOFF ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
s390_short_displacement (rtx disp)
{
  /* No displacement is OK.  */
  if (!disp)
    return true;

  /* Integer displacement in range.  */
  if (GET_CODE (disp) == CONST_INT)
    return INTVAL (disp) >= 0 && INTVAL (disp) < 4096;

  /* GOT offset is not OK, the GOT can be large.  */
  if (GET_CODE (disp) == CONST
      && GET_CODE (XEXP (disp, 0)) == UNSPEC
      && (XINT (XEXP (disp, 0), 1) == UNSPEC_GOT
          || XINT (XEXP (disp, 0), 1) == UNSPEC_GOTNTPOFF))
    return false;

  /* All other symbolic constants are literal pool references,
     which are OK as the literal pool must be small.  */
  if (GET_CODE (disp) == CONST)
    return true;

  return false;
}