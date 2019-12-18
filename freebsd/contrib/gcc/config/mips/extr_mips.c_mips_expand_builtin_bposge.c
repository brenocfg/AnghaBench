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
typedef  enum mips_builtin_type { ____Placeholder_mips_builtin_type } mips_builtin_type ;

/* Variables and functions */
 int /*<<< orphan*/  CCDSP_PO_REGNUM ; 
 int /*<<< orphan*/  CCDSPmode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int MIPS_BUILTIN_BPOSGE32 ; 
 scalar_t__ SImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_GE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_builtin_branch_and_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
mips_expand_builtin_bposge (enum mips_builtin_type builtin_type, rtx target)
{
  rtx condition, cmp_result;
  int cmp_value;

  if (target == 0 || GET_MODE (target) != SImode)
    target = gen_reg_rtx (SImode);

  cmp_result = gen_rtx_REG (CCDSPmode, CCDSP_PO_REGNUM);

  if (builtin_type == MIPS_BUILTIN_BPOSGE32)
    cmp_value = 32;
  else
    gcc_assert (0);

  condition = gen_rtx_GE (VOIDmode, cmp_result, GEN_INT (cmp_value));
  return mips_builtin_branch_and_move (condition, target,
				       const1_rtx, const0_rtx);
}