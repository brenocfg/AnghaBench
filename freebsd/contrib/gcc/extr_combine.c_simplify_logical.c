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
#define  AND 129 
 int const CONST_INT ; 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_BITSIZE (int) ; 
 int /*<<< orphan*/  HOST_BITS_PER_WIDE_INT ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  IOR 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int const XOR ; 
 int /*<<< orphan*/  distribute_and_simplify_rtx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  simplify_and_const_int (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
simplify_logical (rtx x)
{
  enum machine_mode mode = GET_MODE (x);
  rtx op0 = XEXP (x, 0);
  rtx op1 = XEXP (x, 1);

  switch (GET_CODE (x))
    {
    case AND:
      /* We can call simplify_and_const_int only if we don't lose
	 any (sign) bits when converting INTVAL (op1) to
	 "unsigned HOST_WIDE_INT".  */
      if (GET_CODE (op1) == CONST_INT
	  && (GET_MODE_BITSIZE (mode) <= HOST_BITS_PER_WIDE_INT
	      || INTVAL (op1) > 0))
	{
	  x = simplify_and_const_int (x, mode, op0, INTVAL (op1));
	  if (GET_CODE (x) != AND)
	    return x;

	  op0 = XEXP (x, 0);
	  op1 = XEXP (x, 1);
	}

      /* If we have any of (and (ior A B) C) or (and (xor A B) C),
	 apply the distributive law and then the inverse distributive
	 law to see if things simplify.  */
      if (GET_CODE (op0) == IOR || GET_CODE (op0) == XOR)
	{
	  rtx result = distribute_and_simplify_rtx (x, 0);
	  if (result)
	    return result;
	}
      if (GET_CODE (op1) == IOR || GET_CODE (op1) == XOR)
	{
	  rtx result = distribute_and_simplify_rtx (x, 1);
	  if (result)
	    return result;
	}
      break;

    case IOR:
      /* If we have (ior (and A B) C), apply the distributive law and then
	 the inverse distributive law to see if things simplify.  */

      if (GET_CODE (op0) == AND)
	{
	  rtx result = distribute_and_simplify_rtx (x, 0);
	  if (result)
	    return result;
	}

      if (GET_CODE (op1) == AND)
	{
	  rtx result = distribute_and_simplify_rtx (x, 1);
	  if (result)
	    return result;
	}
      break;

    default:
      gcc_unreachable ();
    }

  return x;
}