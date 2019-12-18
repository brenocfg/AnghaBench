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
 int DImode ; 
 int /*<<< orphan*/  MODE_INT ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_sdl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_sdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_swl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mov_swr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_get_unaligned_mem (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mode_for_size (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
mips_expand_unaligned_store (rtx dest, rtx src, unsigned int width, int bitpos)
{
  rtx left, right;
  enum machine_mode mode;

  if (!mips_get_unaligned_mem (&dest, width, bitpos, &left, &right))
    return false;

  mode = mode_for_size (width, MODE_INT, 0);
  src = gen_lowpart (mode, src);

  if (mode == DImode)
    {
      emit_insn (gen_mov_sdl (dest, src, left));
      emit_insn (gen_mov_sdr (copy_rtx (dest), copy_rtx (src), right));
    }
  else
    {
      emit_insn (gen_mov_swl (dest, src, left));
      emit_insn (gen_mov_swr (copy_rtx (dest), copy_rtx (src), right));
    }
  return true;
}