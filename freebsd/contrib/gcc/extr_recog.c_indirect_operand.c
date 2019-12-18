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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SUBREG ; 
 int SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ general_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memory_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reload_completed ; 

int
indirect_operand (rtx op, enum machine_mode mode)
{
  /* Before reload, a SUBREG isn't in memory (see memory_operand, above).  */
  if (! reload_completed
      && GET_CODE (op) == SUBREG && MEM_P (SUBREG_REG (op)))
    {
      int offset = SUBREG_BYTE (op);
      rtx inner = SUBREG_REG (op);

      if (mode != VOIDmode && GET_MODE (op) != mode)
	return 0;

      /* The only way that we can have a general_operand as the resulting
	 address is if OFFSET is zero and the address already is an operand
	 or if the address is (plus Y (const_int -OFFSET)) and Y is an
	 operand.  */

      return ((offset == 0 && general_operand (XEXP (inner, 0), Pmode))
	      || (GET_CODE (XEXP (inner, 0)) == PLUS
		  && GET_CODE (XEXP (XEXP (inner, 0), 1)) == CONST_INT
		  && INTVAL (XEXP (XEXP (inner, 0), 1)) == -offset
		  && general_operand (XEXP (XEXP (inner, 0), 0), Pmode)));
    }

  return (MEM_P (op)
	  && memory_operand (op, mode)
	  && general_operand (XEXP (op, 0), Pmode));
}