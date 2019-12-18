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
 scalar_t__ ALTIVEC_VECTOR_MODE (int) ; 
 scalar_t__ AND ; 
 scalar_t__ CONST_INT ; 
 int DFmode ; 
 int DImode ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ PLUS ; 
 scalar_t__ PRE_DEC ; 
 scalar_t__ PRE_INC ; 
 scalar_t__ REG ; 
 scalar_t__ RS6000_SYMBOL_REF_TLS_P (scalar_t__) ; 
 int /*<<< orphan*/  SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_ALTIVEC ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_POWERPC64 ; 
 scalar_t__ TARGET_UPDATE ; 
 int TFmode ; 
 int TImode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ arg_pointer_rtx ; 
 scalar_t__ legitimate_constant_pool_address_p (scalar_t__) ; 
 scalar_t__ legitimate_indexed_address_p (scalar_t__,int) ; 
 scalar_t__ legitimate_indirect_address_p (scalar_t__,int) ; 
 scalar_t__ legitimate_lo_sum_address_p (int,scalar_t__,int) ; 
 scalar_t__ legitimate_small_data_p (int,scalar_t__) ; 
 scalar_t__ rs6000_legitimate_offset_address_p (int,scalar_t__,int) ; 
 scalar_t__ virtual_stack_vars_rtx ; 

int
rs6000_legitimate_address (enum machine_mode mode, rtx x, int reg_ok_strict)
{
  /* If this is an unaligned stvx/ldvx type address, discard the outer AND.  */
  if (TARGET_ALTIVEC
      && ALTIVEC_VECTOR_MODE (mode)
      && GET_CODE (x) == AND
      && GET_CODE (XEXP (x, 1)) == CONST_INT
      && INTVAL (XEXP (x, 1)) == -16)
    x = XEXP (x, 0);

  if (RS6000_SYMBOL_REF_TLS_P (x))
    return 0;
  if (legitimate_indirect_address_p (x, reg_ok_strict))
    return 1;
  if ((GET_CODE (x) == PRE_INC || GET_CODE (x) == PRE_DEC)
      && !ALTIVEC_VECTOR_MODE (mode)
      && !SPE_VECTOR_MODE (mode)
      && mode != TFmode
      /* Restrict addressing for DI because of our SUBREG hackery.  */
      && !(TARGET_E500_DOUBLE && (mode == DFmode || mode == DImode))
      && TARGET_UPDATE
      && legitimate_indirect_address_p (XEXP (x, 0), reg_ok_strict))
    return 1;
  if (legitimate_small_data_p (mode, x))
    return 1;
  if (legitimate_constant_pool_address_p (x))
    return 1;
  /* If not REG_OK_STRICT (before reload) let pass any stack offset.  */
  if (! reg_ok_strict
      && GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 0)) == REG
      && (XEXP (x, 0) == virtual_stack_vars_rtx
	  || XEXP (x, 0) == arg_pointer_rtx)
      && GET_CODE (XEXP (x, 1)) == CONST_INT)
    return 1;
  if (rs6000_legitimate_offset_address_p (mode, x, reg_ok_strict))
    return 1;
  if (mode != TImode
      && mode != TFmode
      && ((TARGET_HARD_FLOAT && TARGET_FPRS)
	  || TARGET_POWERPC64
	  || ((mode != DFmode || TARGET_E500_DOUBLE) && mode != TFmode))
      && (TARGET_POWERPC64 || mode != DImode)
      && legitimate_indexed_address_p (x, reg_ok_strict))
    return 1;
  if (legitimate_lo_sum_address_p (mode, x, reg_ok_strict))
    return 1;
  return 0;
}