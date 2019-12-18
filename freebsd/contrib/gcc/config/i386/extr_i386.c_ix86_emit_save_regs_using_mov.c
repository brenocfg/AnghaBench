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
typedef  int RTX_FRAME_RELATED_P ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ ix86_save_reg (unsigned int,int) ; 

__attribute__((used)) static void
ix86_emit_save_regs_using_mov (rtx pointer, HOST_WIDE_INT offset)
{
  unsigned int regno;
  rtx insn;

  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (ix86_save_reg (regno, true))
      {
	insn = emit_move_insn (adjust_address (gen_rtx_MEM (Pmode, pointer),
					       Pmode, offset),
			       gen_rtx_REG (Pmode, regno));
	RTX_FRAME_RELATED_P (insn) = 1;
	offset += UNITS_PER_WORD;
      }
}