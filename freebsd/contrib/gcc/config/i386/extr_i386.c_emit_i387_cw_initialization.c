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
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  HImode ; 
#define  I387_CW_CEIL 131 
#define  I387_CW_FLOOR 130 
#define  I387_CW_MASK_PM 129 
#define  I387_CW_TRUNC 128 
 int MAX_386_STACK_LOCALS ; 
 int SLOT_CW_CEIL ; 
 int SLOT_CW_FLOOR ; 
 int SLOT_CW_MASK_PM ; 
 int SLOT_CW_STORED ; 
 int SLOT_CW_TRUNC ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_PARTIAL_REG_STALL ; 
 int /*<<< orphan*/  assign_386_stack_local (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_andhi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_iorhi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movsi_insv_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_fnstcw_1 (int /*<<< orphan*/ ) ; 
 scalar_t__ optimize_size ; 

void
emit_i387_cw_initialization (int mode)
{
  rtx stored_mode = assign_386_stack_local (HImode, SLOT_CW_STORED);
  rtx new_mode;

  int slot;

  rtx reg = gen_reg_rtx (HImode);

  emit_insn (gen_x86_fnstcw_1 (stored_mode));
  emit_move_insn (reg, stored_mode);

  if (TARGET_64BIT || TARGET_PARTIAL_REG_STALL || optimize_size)
    {
      switch (mode)
	{
	case I387_CW_TRUNC:
	  /* round toward zero (truncate) */
	  emit_insn (gen_iorhi3 (reg, reg, GEN_INT (0x0c00)));
	  slot = SLOT_CW_TRUNC;
	  break;

	case I387_CW_FLOOR:
	  /* round down toward -oo */
	  emit_insn (gen_andhi3 (reg, reg, GEN_INT (~0x0c00)));
	  emit_insn (gen_iorhi3 (reg, reg, GEN_INT (0x0400)));
	  slot = SLOT_CW_FLOOR;
	  break;

	case I387_CW_CEIL:
	  /* round up toward +oo */
	  emit_insn (gen_andhi3 (reg, reg, GEN_INT (~0x0c00)));
	  emit_insn (gen_iorhi3 (reg, reg, GEN_INT (0x0800)));
	  slot = SLOT_CW_CEIL;
	  break;

	case I387_CW_MASK_PM:
	  /* mask precision exception for nearbyint() */
	  emit_insn (gen_iorhi3 (reg, reg, GEN_INT (0x0020)));
	  slot = SLOT_CW_MASK_PM;
	  break;

	default:
	  gcc_unreachable ();
	}
    }
  else
    {
      switch (mode)
	{
	case I387_CW_TRUNC:
	  /* round toward zero (truncate) */
	  emit_insn (gen_movsi_insv_1 (reg, GEN_INT (0xc)));
	  slot = SLOT_CW_TRUNC;
	  break;

	case I387_CW_FLOOR:
	  /* round down toward -oo */
	  emit_insn (gen_movsi_insv_1 (reg, GEN_INT (0x4)));
	  slot = SLOT_CW_FLOOR;
	  break;

	case I387_CW_CEIL:
	  /* round up toward +oo */
	  emit_insn (gen_movsi_insv_1 (reg, GEN_INT (0x8)));
	  slot = SLOT_CW_CEIL;
	  break;

	case I387_CW_MASK_PM:
	  /* mask precision exception for nearbyint() */
	  emit_insn (gen_iorhi3 (reg, reg, GEN_INT (0x0020)));
	  slot = SLOT_CW_MASK_PM;
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  gcc_assert (slot < MAX_386_STACK_LOCALS);

  new_mode = assign_386_stack_local (HImode, slot);
  emit_move_insn (new_mode, reg);
}