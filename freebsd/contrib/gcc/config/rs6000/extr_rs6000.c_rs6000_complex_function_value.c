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
 scalar_t__ FLOAT_MODE_P (int) ; 
 unsigned int FP_ARG_RETURN ; 
 int /*<<< orphan*/  GEN_INT (unsigned int) ; 
 int GET_MODE_INNER (int) ; 
 unsigned int GET_MODE_SIZE (int) ; 
 unsigned int GP_ARG_RETURN ; 
 scalar_t__ TARGET_32BIT ; 
 scalar_t__ TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,unsigned int) ; 

__attribute__((used)) static rtx
rs6000_complex_function_value (enum machine_mode mode)
{
  unsigned int regno;
  rtx r1, r2;
  enum machine_mode inner = GET_MODE_INNER (mode);
  unsigned int inner_bytes = GET_MODE_SIZE (inner);

  if (FLOAT_MODE_P (mode) && TARGET_HARD_FLOAT && TARGET_FPRS)
    regno = FP_ARG_RETURN;
  else
    {
      regno = GP_ARG_RETURN;

      /* 32-bit is OK since it'll go in r3/r4.  */
      if (TARGET_32BIT && inner_bytes >= 4)
	return gen_rtx_REG (mode, regno);
    }

  if (inner_bytes >= 8)
    return gen_rtx_REG (mode, regno);

  r1 = gen_rtx_EXPR_LIST (inner, gen_rtx_REG (inner, regno),
			  const0_rtx);
  r2 = gen_rtx_EXPR_LIST (inner, gen_rtx_REG (inner, regno + 1),
			  GEN_INT (inner_bytes));
  return gen_rtx_PARALLEL (mode, gen_rtvec (2, r1, r2));
}