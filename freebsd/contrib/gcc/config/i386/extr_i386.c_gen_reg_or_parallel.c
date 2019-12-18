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
 int BLKmode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int,unsigned int) ; 

__attribute__((used)) static rtx
gen_reg_or_parallel (enum machine_mode mode, enum machine_mode orig_mode,
		     unsigned int regno)
{
  rtx tmp;

  if (orig_mode != BLKmode)
    tmp = gen_rtx_REG (orig_mode, regno);
  else
    {
      tmp = gen_rtx_REG (mode, regno);
      tmp = gen_rtx_EXPR_LIST (VOIDmode, tmp, const0_rtx);
      tmp = gen_rtx_PARALLEL (orig_mode, gen_rtvec (1, tmp));
    }

  return tmp;
}