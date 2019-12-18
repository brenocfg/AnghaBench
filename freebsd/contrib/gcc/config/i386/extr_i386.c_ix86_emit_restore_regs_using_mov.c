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
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  DImode ; 
 int FIRST_PSEUDO_REGISTER ; 
 int FIRST_REX_INT_REG ; 
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ UNITS_PER_WORD ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ix86_save_reg (int,int) ; 
 scalar_t__ trunc_int_for_mode (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ix86_emit_restore_regs_using_mov (rtx pointer, HOST_WIDE_INT offset,
				  int maybe_eh_return)
{
  int regno;
  rtx base_address = gen_rtx_MEM (Pmode, pointer);

  for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (ix86_save_reg (regno, maybe_eh_return))
      {
	/* Ensure that adjust_address won't be forced to produce pointer
	   out of range allowed by x86-64 instruction set.  */
	if (TARGET_64BIT && offset != trunc_int_for_mode (offset, SImode))
	  {
	    rtx r11;

	    r11 = gen_rtx_REG (DImode, FIRST_REX_INT_REG + 3 /* R11 */);
	    emit_move_insn (r11, GEN_INT (offset));
	    emit_insn (gen_adddi3 (r11, r11, pointer));
	    base_address = gen_rtx_MEM (Pmode, r11);
	    offset = 0;
	  }
	emit_move_insn (gen_rtx_REG (Pmode, regno),
			adjust_address (base_address, Pmode, offset));
	offset += UNITS_PER_WORD;
      }
}