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
#define  AND 132 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  IOR 131 
#define  MINUS 130 
#define  PLUS 129 
#define  XOR 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

const char *
arithmetic_instr (rtx op, int shift_first_arg)
{
  switch (GET_CODE (op))
    {
    case PLUS:
      return "add";

    case MINUS:
      return shift_first_arg ? "rsb" : "sub";

    case IOR:
      return "orr";

    case XOR:
      return "eor";

    case AND:
      return "and";

    default:
      gcc_unreachable ();
    }
}