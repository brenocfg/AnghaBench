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
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MINUS ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
plus_minus_operand_p (rtx x)
{
  return GET_CODE (x) == PLUS
         || GET_CODE (x) == MINUS
	 || (GET_CODE (x) == CONST
	     && GET_CODE (XEXP (x, 0)) == PLUS
	     && CONSTANT_P (XEXP (XEXP (x, 0), 0))
	     && CONSTANT_P (XEXP (XEXP (x, 0), 1)));
}