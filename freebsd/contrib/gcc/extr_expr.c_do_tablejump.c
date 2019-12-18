#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {scalar_t__ max_jumptable_ents; } ;

/* Variables and functions */
 int /*<<< orphan*/  CASE_VECTOR_MODE ; 
 int /*<<< orphan*/  CASE_VECTOR_PC_RELATIVE ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTU ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PIC_CASE_VECTOR_ADDRESS (int /*<<< orphan*/ ) ; 
 int Pmode ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
 TYPE_1__* cfun ; 
 int /*<<< orphan*/  convert_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_to_mode (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copy_to_mode_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  gen_const_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MULT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_tablejump (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_address_noforce (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_tablejump (rtx index, enum machine_mode mode, rtx range, rtx table_label,
	      rtx default_label)
{
  rtx temp, vector;

  if (INTVAL (range) > cfun->max_jumptable_ents)
    cfun->max_jumptable_ents = INTVAL (range);

  /* Do an unsigned comparison (in the proper mode) between the index
     expression and the value which represents the length of the range.
     Since we just finished subtracting the lower bound of the range
     from the index expression, this comparison allows us to simultaneously
     check that the original index expression value is both greater than
     or equal to the minimum value of the range and less than or equal to
     the maximum value of the range.  */

  emit_cmp_and_jump_insns (index, range, GTU, NULL_RTX, mode, 1,
			   default_label);

  /* If index is in range, it must fit in Pmode.
     Convert to Pmode so we can index with it.  */
  if (mode != Pmode)
    index = convert_to_mode (Pmode, index, 1);

  /* Don't let a MEM slip through, because then INDEX that comes
     out of PIC_CASE_VECTOR_ADDRESS won't be a valid address,
     and break_out_memory_refs will go to work on it and mess it up.  */
#ifdef PIC_CASE_VECTOR_ADDRESS
  if (flag_pic && !REG_P (index))
    index = copy_to_mode_reg (Pmode, index);
#endif

  /* If flag_force_addr were to affect this address
     it could interfere with the tricky assumptions made
     about addresses that contain label-refs,
     which may be valid only very near the tablejump itself.  */
  /* ??? The only correct use of CASE_VECTOR_MODE is the one inside the
     GET_MODE_SIZE, because this indicates how large insns are.  The other
     uses should all be Pmode, because they are addresses.  This code
     could fail if addresses and insns are not the same size.  */
  index = gen_rtx_PLUS (Pmode,
			gen_rtx_MULT (Pmode, index,
				      GEN_INT (GET_MODE_SIZE (CASE_VECTOR_MODE))),
			gen_rtx_LABEL_REF (Pmode, table_label));
#ifdef PIC_CASE_VECTOR_ADDRESS
  if (flag_pic)
    index = PIC_CASE_VECTOR_ADDRESS (index);
  else
#endif
    index = memory_address_noforce (CASE_VECTOR_MODE, index);
  temp = gen_reg_rtx (CASE_VECTOR_MODE);
  vector = gen_const_mem (CASE_VECTOR_MODE, index);
  convert_move (temp, vector, 0);

  emit_jump_insn (gen_tablejump (temp, table_label));

  /* If we are generating PIC code or if the table is PC-relative, the
     table and JUMP_INSN must be adjacent, so don't output a BARRIER.  */
  if (! CASE_VECTOR_PC_RELATIVE && ! flag_pic)
    emit_barrier ();
}