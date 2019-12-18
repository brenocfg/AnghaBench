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

/* Variables and functions */
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_IF_THEN_ELSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc_rtx ; 
 int /*<<< orphan*/  rs6000_generate_compare (int) ; 

void
rs6000_emit_cbranch (enum rtx_code code, rtx loc)
{
  rtx condition_rtx, loc_ref;

  condition_rtx = rs6000_generate_compare (code);
  loc_ref = gen_rtx_LABEL_REF (VOIDmode, loc);
  emit_jump_insn (gen_rtx_SET (VOIDmode, pc_rtx,
			       gen_rtx_IF_THEN_ELSE (VOIDmode, condition_rtx,
						     loc_ref, pc_rtx)));
}