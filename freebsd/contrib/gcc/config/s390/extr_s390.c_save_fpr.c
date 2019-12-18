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
 int /*<<< orphan*/  DFmode ; 
 int FP_ARG_NUM_REG ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_frame_alias_set () ; 
 int /*<<< orphan*/  get_varargs_alias_set () ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mem_alias_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
save_fpr (rtx base, int offset, int regnum)
{
  rtx addr;
  addr = gen_rtx_MEM (DFmode, plus_constant (base, offset));

  if (regnum >= 16 && regnum <= (16 + FP_ARG_NUM_REG))
    set_mem_alias_set (addr, get_varargs_alias_set ());
  else
    set_mem_alias_set (addr, get_frame_alias_set ());

  return emit_move_insn (addr, gen_rtx_REG (DFmode, regnum));
}