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

/* Variables and functions */
 scalar_t__ BITS_PER_WORD ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_CUID (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 scalar_t__ SUBREG ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 scalar_t__ gen_lowpart (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mem_last_set ; 
 int /*<<< orphan*/  push_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_value_for_reg (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ subreg_lowpart_p (scalar_t__) ; 

__attribute__((used)) static void
record_dead_and_set_regs_1 (rtx dest, rtx setter, void *data)
{
  rtx record_dead_insn = (rtx) data;

  if (GET_CODE (dest) == SUBREG)
    dest = SUBREG_REG (dest);

  if (!record_dead_insn)
    {
      if (REG_P (dest))
	record_value_for_reg (dest, NULL_RTX, NULL_RTX);
      return;
    }

  if (REG_P (dest))
    {
      /* If we are setting the whole register, we know its value.  Otherwise
	 show that we don't know the value.  We can handle SUBREG in
	 some cases.  */
      if (GET_CODE (setter) == SET && dest == SET_DEST (setter))
	record_value_for_reg (dest, record_dead_insn, SET_SRC (setter));
      else if (GET_CODE (setter) == SET
	       && GET_CODE (SET_DEST (setter)) == SUBREG
	       && SUBREG_REG (SET_DEST (setter)) == dest
	       && GET_MODE_BITSIZE (GET_MODE (dest)) <= BITS_PER_WORD
	       && subreg_lowpart_p (SET_DEST (setter)))
	record_value_for_reg (dest, record_dead_insn,
			      gen_lowpart (GET_MODE (dest),
						       SET_SRC (setter)));
      else
	record_value_for_reg (dest, record_dead_insn, NULL_RTX);
    }
  else if (MEM_P (dest)
	   /* Ignore pushes, they clobber nothing.  */
	   && ! push_operand (dest, GET_MODE (dest)))
    mem_last_set = INSN_CUID (record_dead_insn);
}