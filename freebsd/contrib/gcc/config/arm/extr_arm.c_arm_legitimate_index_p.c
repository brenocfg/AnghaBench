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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  scalar_t__ RTX_CODE ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int ASHIFT ; 
 int ASHIFTRT ; 
 int CONST_INT ; 
 int DFmode ; 
 int DImode ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_SIZE (int) ; 
 int HImode ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int LSHIFTRT ; 
 scalar_t__ MODE_FLOAT ; 
 int MULT ; 
 int QImode ; 
 int ROTATERT ; 
 scalar_t__ SIGN_EXTEND ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_FPA ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_LDRD ; 
 scalar_t__ TARGET_MAVERICK ; 
 scalar_t__ TARGET_REALLY_IWMMXT ; 
 scalar_t__ VALID_IWMMXT_REG_MODE (int) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ arm_address_register_rtx_p (int /*<<< orphan*/ ,int) ; 
 scalar_t__ arm_arch4 ; 
 scalar_t__ power_of_two_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_legitimate_index_p (enum machine_mode mode, rtx index, RTX_CODE outer,
			int strict_p)
{
  HOST_WIDE_INT range;
  enum rtx_code code = GET_CODE (index);

  /* Standard coprocessor addressing modes.  */
  if (TARGET_HARD_FLOAT
      && (TARGET_FPA || TARGET_MAVERICK)
      && (GET_MODE_CLASS (mode) == MODE_FLOAT
	  || (TARGET_MAVERICK && mode == DImode)))
    return (code == CONST_INT && INTVAL (index) < 1024
	    && INTVAL (index) > -1024
	    && (INTVAL (index) & 3) == 0);

  if (TARGET_REALLY_IWMMXT && VALID_IWMMXT_REG_MODE (mode))
    {
      /* For DImode assume values will usually live in core regs
	 and only allow LDRD addressing modes.  */
      if (!TARGET_LDRD || mode != DImode)
	return (code == CONST_INT
		&& INTVAL (index) < 1024
		&& INTVAL (index) > -1024
		&& (INTVAL (index) & 3) == 0);
    }

  if (arm_address_register_rtx_p (index, strict_p)
      && (GET_MODE_SIZE (mode) <= 4))
    return 1;

  if (mode == DImode || mode == DFmode)
    {
      if (code == CONST_INT)
	{
	  HOST_WIDE_INT val = INTVAL (index);

	  if (TARGET_LDRD)
	    return val > -256 && val < 256;
	  else
	    return val > -4096 && val < 4092;
	}

      return TARGET_LDRD && arm_address_register_rtx_p (index, strict_p);
    }

  if (GET_MODE_SIZE (mode) <= 4
      && ! (arm_arch4
	    && (mode == HImode
		|| (mode == QImode && outer == SIGN_EXTEND))))
    {
      if (code == MULT)
	{
	  rtx xiop0 = XEXP (index, 0);
	  rtx xiop1 = XEXP (index, 1);

	  return ((arm_address_register_rtx_p (xiop0, strict_p)
		   && power_of_two_operand (xiop1, SImode))
		  || (arm_address_register_rtx_p (xiop1, strict_p)
		      && power_of_two_operand (xiop0, SImode)));
	}
      else if (code == LSHIFTRT || code == ASHIFTRT
	       || code == ASHIFT || code == ROTATERT)
	{
	  rtx op = XEXP (index, 1);

	  return (arm_address_register_rtx_p (XEXP (index, 0), strict_p)
		  && GET_CODE (op) == CONST_INT
		  && INTVAL (op) > 0
		  && INTVAL (op) <= 31);
	}
    }

  /* For ARM v4 we may be doing a sign-extend operation during the
     load.  */
  if (arm_arch4)
    {
      if (mode == HImode || (outer == SIGN_EXTEND && mode == QImode))
	range = 256;
      else
	range = 4096;
    }
  else
    range = (mode == HImode) ? 4095 : 4096;

  return (code == CONST_INT
	  && INTVAL (index) < range
	  && INTVAL (index) > -range);
}