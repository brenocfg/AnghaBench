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

/* Variables and functions */
 int /*<<< orphan*/  CONST0_RTX (int /*<<< orphan*/ ) ; 
 scalar_t__ FP_INC ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SFmode ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gen_slt_sf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ true_regnum (int /*<<< orphan*/ ) ; 

void
mips_emit_fcc_reload (rtx dest, rtx src, rtx scratch)
{
  rtx fp1, fp2;

  /* Change the source to SFmode.  */
  if (MEM_P (src))
    src = adjust_address (src, SFmode, 0);
  else if (REG_P (src) || GET_CODE (src) == SUBREG)
    src = gen_rtx_REG (SFmode, true_regnum (src));

  fp1 = gen_rtx_REG (SFmode, REGNO (scratch));
  fp2 = gen_rtx_REG (SFmode, REGNO (scratch) + FP_INC);

  emit_move_insn (copy_rtx (fp1), src);
  emit_move_insn (copy_rtx (fp2), CONST0_RTX (SFmode));
  emit_insn (gen_slt_sf (dest, fp2, fp1));
}