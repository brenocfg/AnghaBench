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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ALTIVEC_REGNO_P (int) ; 
 int ALTIVEC_VECTOR_MODE (int) ; 
 scalar_t__ CR_REGNO_P (int) ; 
 int /*<<< orphan*/  DECIMAL_FLOAT_MODE_P (int) ; 
 scalar_t__ FP_REGNO_P (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int HARD_REGNO_NREGS (int,int) ; 
 int INT_REGNO_P (int) ; 
 scalar_t__ MODE_CC ; 
 scalar_t__ MODE_INT ; 
 int PSImode ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 scalar_t__ SPE_SIMD_REGNO_P (int) ; 
 scalar_t__ SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_SPE ; 
 scalar_t__ UNITS_PER_FP_WORD ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ XER_REGNO_P (int) ; 

__attribute__((used)) static int
rs6000_hard_regno_mode_ok (int regno, enum machine_mode mode)
{
  /* The GPRs can hold any mode, but values bigger than one register
     cannot go past R31.  */
  if (INT_REGNO_P (regno))
    return INT_REGNO_P (regno + HARD_REGNO_NREGS (regno, mode) - 1);

  /* The float registers can only hold floating modes and DImode.
     This also excludes decimal float modes.  */
  if (FP_REGNO_P (regno))
    return
      (SCALAR_FLOAT_MODE_P (mode)
       && !DECIMAL_FLOAT_MODE_P (mode)
       && FP_REGNO_P (regno + HARD_REGNO_NREGS (regno, mode) - 1))
      || (GET_MODE_CLASS (mode) == MODE_INT
	  && GET_MODE_SIZE (mode) == UNITS_PER_FP_WORD);

  /* The CR register can only hold CC modes.  */
  if (CR_REGNO_P (regno))
    return GET_MODE_CLASS (mode) == MODE_CC;

  if (XER_REGNO_P (regno))
    return mode == PSImode;

  /* AltiVec only in AldyVec registers.  */
  if (ALTIVEC_REGNO_P (regno))
    return ALTIVEC_VECTOR_MODE (mode);

  /* ...but GPRs can hold SIMD data on the SPE in one register.  */
  if (SPE_SIMD_REGNO_P (regno) && TARGET_SPE && SPE_VECTOR_MODE (mode))
    return 1;

  /* We cannot put TImode anywhere except general register and it must be
     able to fit within the register set.  */

  return GET_MODE_SIZE (mode) <= UNITS_PER_WORD;
}