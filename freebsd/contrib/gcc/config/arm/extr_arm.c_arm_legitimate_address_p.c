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
typedef  int /*<<< orphan*/  RTX_CODE ;

/* Variables and functions */
 int CONST ; 
 scalar_t__ CONSTANT_POOL_ADDRESS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 int DFmode ; 
 int DImode ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_SIZE (int) ; 
 int LABEL_REF ; 
 scalar_t__ MINUS ; 
 scalar_t__ MODE_FLOAT ; 
 scalar_t__ PLUS ; 
 int POST_DEC ; 
 int POST_INC ; 
 int POST_MODIFY ; 
 int PRE_DEC ; 
 int PRE_INC ; 
 int PRE_MODIFY ; 
 scalar_t__ REG ; 
 int SYMBOL_REF ; 
 scalar_t__ TARGET_LDRD ; 
 scalar_t__ TARGET_SOFT_FLOAT ; 
 scalar_t__ TARGET_VFP ; 
 int TImode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int arm_address_register_rtx_p (int /*<<< orphan*/ ,int) ; 
 scalar_t__ arm_legitimate_index_p (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  get_pool_constant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcrel_constant_p (int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ symbol_mentioned_p (int /*<<< orphan*/ ) ; 

int
arm_legitimate_address_p (enum machine_mode mode, rtx x, RTX_CODE outer,
			  int strict_p)
{
  bool use_ldrd;
  enum rtx_code code = GET_CODE (x);

  if (arm_address_register_rtx_p (x, strict_p))
    return 1;

  use_ldrd = (TARGET_LDRD
	      && (mode == DImode
		  || (mode == DFmode && (TARGET_SOFT_FLOAT || TARGET_VFP))));

  if (code == POST_INC || code == PRE_DEC
      || ((code == PRE_INC || code == POST_DEC)
	  && (use_ldrd || GET_MODE_SIZE (mode) <= 4)))
    return arm_address_register_rtx_p (XEXP (x, 0), strict_p);

  else if ((code == POST_MODIFY || code == PRE_MODIFY)
	   && arm_address_register_rtx_p (XEXP (x, 0), strict_p)
	   && GET_CODE (XEXP (x, 1)) == PLUS
	   && rtx_equal_p (XEXP (XEXP (x, 1), 0), XEXP (x, 0)))
    {
      rtx addend = XEXP (XEXP (x, 1), 1);

      /* Don't allow ldrd post increment by register because it's hard
	 to fixup invalid register choices.  */
      if (use_ldrd
	  && GET_CODE (x) == POST_MODIFY
	  && GET_CODE (addend) == REG)
	return 0;

      return ((use_ldrd || GET_MODE_SIZE (mode) <= 4)
	      && arm_legitimate_index_p (mode, addend, outer, strict_p));
    }

  /* After reload constants split into minipools will have addresses
     from a LABEL_REF.  */
  else if (reload_completed
	   && (code == LABEL_REF
	       || (code == CONST
		   && GET_CODE (XEXP (x, 0)) == PLUS
		   && GET_CODE (XEXP (XEXP (x, 0), 0)) == LABEL_REF
		   && GET_CODE (XEXP (XEXP (x, 0), 1)) == CONST_INT)))
    return 1;

  else if (mode == TImode)
    return 0;

  else if (code == PLUS)
    {
      rtx xop0 = XEXP (x, 0);
      rtx xop1 = XEXP (x, 1);

      return ((arm_address_register_rtx_p (xop0, strict_p)
	       && arm_legitimate_index_p (mode, xop1, outer, strict_p))
	      || (arm_address_register_rtx_p (xop1, strict_p)
		  && arm_legitimate_index_p (mode, xop0, outer, strict_p)));
    }

#if 0
  /* Reload currently can't handle MINUS, so disable this for now */
  else if (GET_CODE (x) == MINUS)
    {
      rtx xop0 = XEXP (x, 0);
      rtx xop1 = XEXP (x, 1);

      return (arm_address_register_rtx_p (xop0, strict_p)
	      && arm_legitimate_index_p (mode, xop1, outer, strict_p));
    }
#endif

  else if (GET_MODE_CLASS (mode) != MODE_FLOAT
	   && code == SYMBOL_REF
	   && CONSTANT_POOL_ADDRESS_P (x)
	   && ! (flag_pic
		 && symbol_mentioned_p (get_pool_constant (x))
		 && ! pcrel_constant_p (get_pool_constant (x))))
    return 1;

  return 0;
}