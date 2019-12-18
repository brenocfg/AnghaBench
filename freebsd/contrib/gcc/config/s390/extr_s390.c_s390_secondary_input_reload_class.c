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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int ADDR_REGS ; 
 int /*<<< orphan*/  CC_REGS ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  DISP_IN_RANGE (scalar_t__) ; 
 int /*<<< orphan*/  FP_REGS ; 
 int GENERAL_REGS ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM ; 
 int NO_REGS ; 
 scalar_t__ PLUS ; 
 int TFmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ reg_classes_intersect_p (int /*<<< orphan*/ ,int) ; 
 scalar_t__ s390_plus_operand (int /*<<< orphan*/ ,int) ; 

enum reg_class
s390_secondary_input_reload_class (enum reg_class class,
				   enum machine_mode mode, rtx in)
{
  if (s390_plus_operand (in, mode))
    return ADDR_REGS;

  if (reg_classes_intersect_p (FP_REGS, class)
      && mode == TFmode
      && GET_CODE (in) == MEM
      && GET_CODE (XEXP (in, 0)) == PLUS
      && GET_CODE (XEXP (XEXP (in, 0), 1)) == CONST_INT
      && !DISP_IN_RANGE (INTVAL (XEXP (XEXP (in, 0), 1))
			 + GET_MODE_SIZE (mode) - 1))
    return ADDR_REGS;

  if (reg_classes_intersect_p (CC_REGS, class))
    return GENERAL_REGS;

  return NO_REGS;
}