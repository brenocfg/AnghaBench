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
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GP_REG_FIRST ; 
 int /*<<< orphan*/  M16_REG_P (scalar_t__) ; 
 int /*<<< orphan*/  MIPS_EPILOGUE_TEMP (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_MIPS16 ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mips_restore_reg (rtx reg, rtx mem)
{
  /* There's no mips16 instruction to load $31 directly.  Load into
     $7 instead and adjust the return insn appropriately.  */
  if (TARGET_MIPS16 && REGNO (reg) == GP_REG_FIRST + 31)
    reg = gen_rtx_REG (GET_MODE (reg), 7);

  if (TARGET_MIPS16 && !M16_REG_P (REGNO (reg)))
    {
      /* Can't restore directly; move through a temporary.  */
      emit_move_insn (MIPS_EPILOGUE_TEMP (GET_MODE (reg)), mem);
      emit_move_insn (reg, MIPS_EPILOGUE_TEMP (GET_MODE (reg)));
    }
  else
    emit_move_insn (reg, mem);
}