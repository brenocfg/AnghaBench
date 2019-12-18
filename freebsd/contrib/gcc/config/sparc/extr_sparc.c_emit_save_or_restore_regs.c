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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_V9 ; 
 int /*<<< orphan*/  VOIDmode ; 
 int apparent_fsize ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int frame_base_offset ; 
 int /*<<< orphan*/  frame_base_reg ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int num_gfregs ; 
 int save_or_restore_regs (int,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
emit_save_or_restore_regs (int action)
{
  HOST_WIDE_INT offset;
  rtx base;

  offset = frame_base_offset - apparent_fsize;

  if (offset < -4096 || offset + num_gfregs * 4 > 4095)
    {
      /* ??? This might be optimized a little as %g1 might already have a
	 value close enough that a single add insn will do.  */
      /* ??? Although, all of this is probably only a temporary fix
	 because if %g1 can hold a function result, then
	 sparc_expand_epilogue will lose (the result will be
	 clobbered).  */
      base = gen_rtx_REG (Pmode, 1);
      emit_move_insn (base, GEN_INT (offset));
      emit_insn (gen_rtx_SET (VOIDmode,
			      base,
			      gen_rtx_PLUS (Pmode, frame_base_reg, base)));
      offset = 0;
    }
  else
    base = frame_base_reg;

  offset = save_or_restore_regs (0, 8, base, offset, action);
  save_or_restore_regs (32, TARGET_V9 ? 96 : 64, base, offset, action);
}