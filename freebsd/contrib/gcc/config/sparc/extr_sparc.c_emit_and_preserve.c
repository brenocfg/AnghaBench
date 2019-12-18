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
typedef  scalar_t__ rtx ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int SPARC_STACK_ALIGN (int) ; 
 int SPARC_STACK_BIAS ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ adjust_address (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 scalar_t__ gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_stack_pointer_dec (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_stack_pointer_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static void
emit_and_preserve (rtx seq, rtx reg, rtx reg2)
{
  /* We must preserve the lowest 16 words for the register save area.  */
  HOST_WIDE_INT offset = 16*UNITS_PER_WORD;
  /* We really need only 2 words of fresh stack space.  */
  HOST_WIDE_INT size = SPARC_STACK_ALIGN (offset + 2*UNITS_PER_WORD);

  rtx slot
    = gen_rtx_MEM (word_mode, plus_constant (stack_pointer_rtx,
					     SPARC_STACK_BIAS + offset));

  emit_insn (gen_stack_pointer_dec (GEN_INT (size)));
  emit_insn (gen_rtx_SET (VOIDmode, slot, reg));
  if (reg2)
    emit_insn (gen_rtx_SET (VOIDmode,
			    adjust_address (slot, word_mode, UNITS_PER_WORD),
			    reg2));
  emit_insn (seq);
  if (reg2)
    emit_insn (gen_rtx_SET (VOIDmode,
			    reg2,
			    adjust_address (slot, word_mode, UNITS_PER_WORD)));
  emit_insn (gen_rtx_SET (VOIDmode, reg, slot));
  emit_insn (gen_stack_pointer_inc (GEN_INT (size)));
}