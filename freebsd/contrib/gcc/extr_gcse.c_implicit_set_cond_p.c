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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ HONOR_SIGNED_ZEROS (int) ; 
 scalar_t__ REAL_VALUES_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dconst0 ; 
 int gcse_constant_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
implicit_set_cond_p (rtx cond)
{
  enum machine_mode mode = GET_MODE (XEXP (cond, 0));
  rtx cst = XEXP (cond, 1);

  /* We can't perform this optimization if either operand might be or might
     contain a signed zero.  */
  if (HONOR_SIGNED_ZEROS (mode))
    {
      /* It is sufficient to check if CST is or contains a zero.  We must
	 handle float, complex, and vector.  If any subpart is a zero, then
	 the optimization can't be performed.  */
      /* ??? The complex and vector checks are not implemented yet.  We just
	 always return zero for them.  */
      if (GET_CODE (cst) == CONST_DOUBLE)
	{
	  REAL_VALUE_TYPE d;
	  REAL_VALUE_FROM_CONST_DOUBLE (d, cst);
	  if (REAL_VALUES_EQUAL (d, dconst0))
	    return 0;
	}
      else
	return 0;
    }

  return gcse_constant_p (cst);
}