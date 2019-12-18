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
 int /*<<< orphan*/  BINARY_P (int /*<<< orphan*/ ) ; 
 int CONST_INT ; 
#define  DIV 132 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  MOD 131 
#define  MULT 130 
#define  UDIV 129 
#define  UMOD 128 
 int /*<<< orphan*/  UNARY_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  exact_log2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
contains_muldiv (rtx x)
{
  switch (GET_CODE (x))
    {
    case MOD:  case DIV:  case UMOD:  case UDIV:
      return 1;

    case MULT:
      return ! (GET_CODE (XEXP (x, 1)) == CONST_INT
		&& exact_log2 (INTVAL (XEXP (x, 1))) >= 0);
    default:
      if (BINARY_P (x))
	return contains_muldiv (XEXP (x, 0))
	    || contains_muldiv (XEXP (x, 1));

      if (UNARY_P (x))
	return contains_muldiv (XEXP (x, 0));

      return 0;
    }
}