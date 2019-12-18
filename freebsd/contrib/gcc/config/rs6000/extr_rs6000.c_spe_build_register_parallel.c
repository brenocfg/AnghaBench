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
#define  DCmode 129 
#define  DFmode 128 
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  gen_rtx_EXPR_LIST (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
spe_build_register_parallel (enum machine_mode mode, int gregno)
{
  rtx r1, r3;

  switch (mode)
    {
    case DFmode:
      r1 = gen_rtx_REG (DImode, gregno);
      r1 = gen_rtx_EXPR_LIST (VOIDmode, r1, const0_rtx);
      return gen_rtx_PARALLEL (mode, gen_rtvec (1, r1));

    case DCmode:
      r1 = gen_rtx_REG (DImode, gregno);
      r1 = gen_rtx_EXPR_LIST (VOIDmode, r1, const0_rtx);
      r3 = gen_rtx_REG (DImode, gregno + 2);
      r3 = gen_rtx_EXPR_LIST (VOIDmode, r3, GEN_INT (8));
      return gen_rtx_PARALLEL (mode, gen_rtvec (2, r1, r3));

    default:
      gcc_unreachable ();
    }
}