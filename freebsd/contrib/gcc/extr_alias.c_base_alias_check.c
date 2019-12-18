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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ADDRESS ; 
 scalar_t__ AND ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_UNIT_SIZE (int) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ Pmode ; 
 scalar_t__ VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ canon_rtx (scalar_t__) ; 
 scalar_t__ find_base_term (scalar_t__) ; 
 int flag_argument_noalias ; 
 int /*<<< orphan*/  flag_expensive_optimizations ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
base_alias_check (rtx x, rtx y, enum machine_mode x_mode,
		  enum machine_mode y_mode)
{
  rtx x_base = find_base_term (x);
  rtx y_base = find_base_term (y);

  /* If the address itself has no known base see if a known equivalent
     value has one.  If either address still has no known base, nothing
     is known about aliasing.  */
  if (x_base == 0)
    {
      rtx x_c;

      if (! flag_expensive_optimizations || (x_c = canon_rtx (x)) == x)
	return 1;

      x_base = find_base_term (x_c);
      if (x_base == 0)
	return 1;
    }

  if (y_base == 0)
    {
      rtx y_c;
      if (! flag_expensive_optimizations || (y_c = canon_rtx (y)) == y)
	return 1;

      y_base = find_base_term (y_c);
      if (y_base == 0)
	return 1;
    }

  /* If the base addresses are equal nothing is known about aliasing.  */
  if (rtx_equal_p (x_base, y_base))
    return 1;

  /* The base addresses of the read and write are different expressions.
     If they are both symbols and they are not accessed via AND, there is
     no conflict.  We can bring knowledge of object alignment into play
     here.  For example, on alpha, "char a, b;" can alias one another,
     though "char a; long b;" cannot.  */
  if (GET_CODE (x_base) != ADDRESS && GET_CODE (y_base) != ADDRESS)
    {
      if (GET_CODE (x) == AND && GET_CODE (y) == AND)
	return 1;
      if (GET_CODE (x) == AND
	  && (GET_CODE (XEXP (x, 1)) != CONST_INT
	      || (int) GET_MODE_UNIT_SIZE (y_mode) < -INTVAL (XEXP (x, 1))))
	return 1;
      if (GET_CODE (y) == AND
	  && (GET_CODE (XEXP (y, 1)) != CONST_INT
	      || (int) GET_MODE_UNIT_SIZE (x_mode) < -INTVAL (XEXP (y, 1))))
	return 1;
      /* Differing symbols never alias.  */
      return 0;
    }

  /* If one address is a stack reference there can be no alias:
     stack references using different base registers do not alias,
     a stack reference can not alias a parameter, and a stack reference
     can not alias a global.  */
  if ((GET_CODE (x_base) == ADDRESS && GET_MODE (x_base) == Pmode)
      || (GET_CODE (y_base) == ADDRESS && GET_MODE (y_base) == Pmode))
    return 0;

  if (! flag_argument_noalias)
    return 1;

  if (flag_argument_noalias > 1)
    return 0;

  /* Weak noalias assertion (arguments are distinct, but may match globals).  */
  return ! (GET_MODE (x_base) == VOIDmode && GET_MODE (y_base) == VOIDmode);
}