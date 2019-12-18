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
 int /*<<< orphan*/  REG_EQUAL ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_insn_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_reg_equal_equiv_note (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unique_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
gcse_emit_move_after (rtx src, rtx dest, rtx insn)
{
  rtx new;
  rtx set = single_set (insn), set2;
  rtx note;
  rtx eqv;

  /* This should never fail since we're creating a reg->reg copy
     we've verified to be valid.  */

  new = emit_insn_after (gen_move_insn (dest, src), insn);

  /* Note the equivalence for local CSE pass.  */
  set2 = single_set (new);
  if (!set2 || !rtx_equal_p (SET_DEST (set2), dest))
    return new;
  if ((note = find_reg_equal_equiv_note (insn)))
    eqv = XEXP (note, 0);
  else
    eqv = SET_SRC (set);

  set_unique_reg_note (new, REG_EQUAL, copy_insn_1 (eqv));

  return new;
}