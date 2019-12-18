#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {TYPE_1__* handlers; } ;
struct TYPE_3__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 scalar_t__ BIGGEST_ALIGNMENT ; 
 int /*<<< orphan*/  BLOCK_OP_NO_LIBCALL ; 
 scalar_t__ CODE_FOR_nothing ; 
 scalar_t__ CONCAT ; 
 int /*<<< orphan*/  CONSTANT_P (scalar_t__) ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 size_t GET_MODE_INNER (int) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
 int MEM_P (scalar_t__) ; 
 scalar_t__ MODE_COMPLEX_FLOAT ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  STRICT_ALIGNMENT ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_block_move (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ emit_move_complex_push (int,scalar_t__,scalar_t__) ; 
 scalar_t__ emit_move_via_integer (int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_last_insn () ; 
 scalar_t__ get_mode_alignment (int) ; 
 TYPE_2__* mov_optab ; 
 scalar_t__ push_operand (scalar_t__,int) ; 
 int /*<<< orphan*/  read_complex_part (scalar_t__,int) ; 
 int /*<<< orphan*/  reg_overlap_mentioned_p (scalar_t__,scalar_t__) ; 
 scalar_t__ register_operand (scalar_t__,int) ; 
 int /*<<< orphan*/  reload_completed ; 
 int /*<<< orphan*/  reload_in_progress ; 
 int /*<<< orphan*/  write_complex_part (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static rtx
emit_move_complex (enum machine_mode mode, rtx x, rtx y)
{
  bool try_int;

  /* Need to take special care for pushes, to maintain proper ordering
     of the data, and possibly extra padding.  */
  if (push_operand (x, mode))
    return emit_move_complex_push (mode, x, y);

  /* See if we can coerce the target into moving both values at once.  */

  /* Move floating point as parts.  */
  if (GET_MODE_CLASS (mode) == MODE_COMPLEX_FLOAT
      && mov_optab->handlers[GET_MODE_INNER (mode)].insn_code != CODE_FOR_nothing)
    try_int = false;
  /* Not possible if the values are inherently not adjacent.  */
  else if (GET_CODE (x) == CONCAT || GET_CODE (y) == CONCAT)
    try_int = false;
  /* Is possible if both are registers (or subregs of registers).  */
  else if (register_operand (x, mode) && register_operand (y, mode))
    try_int = true;
  /* If one of the operands is a memory, and alignment constraints
     are friendly enough, we may be able to do combined memory operations.
     We do not attempt this if Y is a constant because that combination is
     usually better with the by-parts thing below.  */
  else if ((MEM_P (x) ? !CONSTANT_P (y) : MEM_P (y))
	   && (!STRICT_ALIGNMENT
	       || get_mode_alignment (mode) == BIGGEST_ALIGNMENT))
    try_int = true;
  else
    try_int = false;

  if (try_int)
    {
      rtx ret;

      /* For memory to memory moves, optimal behavior can be had with the
	 existing block move logic.  */
      if (MEM_P (x) && MEM_P (y))
	{
	  emit_block_move (x, y, GEN_INT (GET_MODE_SIZE (mode)),
			   BLOCK_OP_NO_LIBCALL);
	  return get_last_insn ();
	}

      ret = emit_move_via_integer (mode, x, y, true);
      if (ret)
	return ret;
    }

  /* Show the output dies here.  This is necessary for SUBREGs
     of pseudos since we cannot track their lifetimes correctly;
     hard regs shouldn't appear here except as return values.  */
  if (!reload_completed && !reload_in_progress
      && REG_P (x) && !reg_overlap_mentioned_p (x, y))
    emit_insn (gen_rtx_CLOBBER (VOIDmode, x));

  write_complex_part (x, read_complex_part (y, false), false);
  write_complex_part (x, read_complex_part (y, true), true);
  return get_last_insn ();
}