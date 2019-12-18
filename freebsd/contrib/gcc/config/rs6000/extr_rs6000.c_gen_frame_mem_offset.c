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
 int DFmode ; 
 int /*<<< orphan*/  FIXED_SCRATCH ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SPE_VECTOR_MODE (int) ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_SPE_ABI ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_frame_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
gen_frame_mem_offset (enum machine_mode mode, rtx reg, int offset)
{
  rtx int_rtx, offset_rtx;

  int_rtx = GEN_INT (offset);

  if ((TARGET_SPE_ABI && SPE_VECTOR_MODE (mode))
      || (TARGET_E500_DOUBLE && mode == DFmode))
    {
      offset_rtx = gen_rtx_REG (Pmode, FIXED_SCRATCH);
      emit_move_insn (offset_rtx, int_rtx);
    }
  else
    offset_rtx = int_rtx;

  return gen_frame_mem (mode, gen_rtx_PLUS (Pmode, reg, offset_rtx));
}