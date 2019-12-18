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
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  INTVAL (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PLUS ; 
 scalar_t__ REG ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 

bool
s390_decompose_shift_count (rtx op, rtx *base, HOST_WIDE_INT *offset)
{
  HOST_WIDE_INT off = 0;

  /* We can have an integer constant, an address register,
     or a sum of the two.  */
  if (GET_CODE (op) == CONST_INT)
    {
      off = INTVAL (op);
      op = NULL_RTX;
    }
  if (op && GET_CODE (op) == PLUS && GET_CODE (XEXP (op, 1)) == CONST_INT)
    {
      off = INTVAL (XEXP (op, 1));
      op = XEXP (op, 0);
    }
  while (op && GET_CODE (op) == SUBREG)
    op = SUBREG_REG (op);

  if (op && GET_CODE (op) != REG)
    return false;

  if (offset)
    *offset = off;
  if (base)
    *base = op;

   return true;
}