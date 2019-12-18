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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
#define  AND 132 
 int /*<<< orphan*/  ARM_SIGN_EXTEND (int /*<<< orphan*/ ) ; 
#define  IOR 131 
#define  MINUS 130 
#define  PLUS 129 
#define  XOR 128 
 int const_ok_for_arm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static int
const_ok_for_op (HOST_WIDE_INT i, enum rtx_code code)
{
  if (const_ok_for_arm (i))
    return 1;

  switch (code)
    {
    case PLUS:
      return const_ok_for_arm (ARM_SIGN_EXTEND (-i));

    case MINUS:		/* Should only occur with (MINUS I reg) => rsb */
    case XOR:
    case IOR:
      return 0;

    case AND:
      return const_ok_for_arm (ARM_SIGN_EXTEND (~i));

    default:
      gcc_unreachable ();
    }
}