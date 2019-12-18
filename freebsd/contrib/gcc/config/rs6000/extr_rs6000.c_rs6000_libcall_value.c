#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ split_complex_arg; } ;
struct TYPE_4__ {TYPE_1__ calls; } ;

/* Variables and functions */
 unsigned int ALTIVEC_ARG_RETURN ; 
 scalar_t__ ALTIVEC_VECTOR_MODE (int) ; 
 scalar_t__ COMPLEX_MODE_P (int) ; 
 int DCmode ; 
 scalar_t__ DECIMAL_FLOAT_MODE_P (int) ; 
 int DFmode ; 
 int DImode ; 
 unsigned int FP_ARG_RETURN ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int GP_ARG_RETURN ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 int SImode ; 
 scalar_t__ TARGET_32BIT ; 
 scalar_t__ TARGET_ALTIVEC ; 
 scalar_t__ TARGET_ALTIVEC_ABI ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_POWERPC64 ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,unsigned int) ; 
 int /*<<< orphan*/  rs6000_complex_function_value (int) ; 
 int /*<<< orphan*/  spe_build_register_parallel (int,int) ; 
 TYPE_2__ targetm ; 

rtx
rs6000_libcall_value (enum machine_mode mode)
{
  unsigned int regno;

  if (TARGET_32BIT && TARGET_POWERPC64 && mode == DImode)
    {
      /* Long long return value need be split in -mpowerpc64, 32bit ABI.  */
      return gen_rtx_PARALLEL (DImode,
	gen_rtvec (2,
		   gen_rtx_EXPR_LIST (VOIDmode,
				      gen_rtx_REG (SImode, GP_ARG_RETURN),
				      const0_rtx),
		   gen_rtx_EXPR_LIST (VOIDmode,
				      gen_rtx_REG (SImode,
						   GP_ARG_RETURN + 1),
				      GEN_INT (4))));
    }

  if (DECIMAL_FLOAT_MODE_P (mode))
    regno = GP_ARG_RETURN;
  else if (SCALAR_FLOAT_MODE_P (mode)
	   && TARGET_HARD_FLOAT && TARGET_FPRS)
    regno = FP_ARG_RETURN;
  else if (ALTIVEC_VECTOR_MODE (mode)
	   && TARGET_ALTIVEC && TARGET_ALTIVEC_ABI)
    regno = ALTIVEC_ARG_RETURN;
  else if (COMPLEX_MODE_P (mode) && targetm.calls.split_complex_arg)
    return rs6000_complex_function_value (mode);
  else if (TARGET_E500_DOUBLE && TARGET_HARD_FLOAT
	   && (mode == DFmode || mode == DCmode))
    return spe_build_register_parallel (mode, GP_ARG_RETURN);
  else
    regno = GP_ARG_RETURN;

  return gen_rtx_REG (mode, regno);
}