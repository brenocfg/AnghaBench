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
 scalar_t__ DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int MAX_MOVE_BYTES ; 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int /*<<< orphan*/  PLUS ; 
 scalar_t__ Pmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_simple_binop (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_bne (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpdi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  mips_adjust_block_mem (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_block_move_straight (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mips_block_move_loop (rtx dest, rtx src, HOST_WIDE_INT length)
{
  rtx label, src_reg, dest_reg, final_src;
  HOST_WIDE_INT leftover;

  leftover = length % MAX_MOVE_BYTES;
  length -= leftover;

  /* Create registers and memory references for use within the loop.  */
  mips_adjust_block_mem (src, MAX_MOVE_BYTES, &src_reg, &src);
  mips_adjust_block_mem (dest, MAX_MOVE_BYTES, &dest_reg, &dest);

  /* Calculate the value that SRC_REG should have after the last iteration
     of the loop.  */
  final_src = expand_simple_binop (Pmode, PLUS, src_reg, GEN_INT (length),
				   0, 0, OPTAB_WIDEN);

  /* Emit the start of the loop.  */
  label = gen_label_rtx ();
  emit_label (label);

  /* Emit the loop body.  */
  mips_block_move_straight (dest, src, MAX_MOVE_BYTES);

  /* Move on to the next block.  */
  emit_move_insn (src_reg, plus_constant (src_reg, MAX_MOVE_BYTES));
  emit_move_insn (dest_reg, plus_constant (dest_reg, MAX_MOVE_BYTES));

  /* Emit the loop condition.  */
  if (Pmode == DImode)
    emit_insn (gen_cmpdi (src_reg, final_src));
  else
    emit_insn (gen_cmpsi (src_reg, final_src));
  emit_jump_insn (gen_bne (label));

  /* Mop up any left-over bytes.  */
  if (leftover)
    mips_block_move_straight (dest, src, leftover);
}