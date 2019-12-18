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
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum direction { ____Placeholder_direction } direction ;

/* Variables and functions */
 int /*<<< orphan*/  ACCUMULATE_OUTGOING_ARGS ; 
 unsigned int BIGGEST_ALIGNMENT ; 
 int BITS_PER_UNIT ; 
 int BLKmode ; 
 int /*<<< orphan*/  BLOCK_OP_CALL_PARM ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int FUNCTION_ARG_PADDING (int,int /*<<< orphan*/ ) ; 
 scalar_t__ GEN_INT (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int /*<<< orphan*/ ) ; 
 int GET_MODE_SIZE (int) ; 
 int INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  LEGITIMATE_CONSTANT_P (scalar_t__) ; 
 unsigned int MEM_ALIGN (scalar_t__) ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ MOVE_BY_PIECES_P (unsigned int,unsigned int) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 scalar_t__ PARALLEL ; 
 int PARM_BOUNDARY ; 
 scalar_t__ POST_DEC ; 
 scalar_t__ PUSH_ARGS ; 
 int PUSH_ROUNDING (int) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SLOW_UNALIGNED_ACCESS (int,unsigned int) ; 
 scalar_t__ STACK_PUSH_CODE ; 
 int UNITS_PER_WORD ; 
 scalar_t__ adjust_address (scalar_t__,int,int) ; 
 int /*<<< orphan*/  anti_adjust_stack (scalar_t__) ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 int downward ; 
 int /*<<< orphan*/  emit_block_move (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_group_load (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_single_push_insn (int,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_const_mem (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_rtx_MEM (int,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ memory_address (int,scalar_t__) ; 
 int /*<<< orphan*/  move_block_to_reg (scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  move_by_pieces (int /*<<< orphan*/ *,scalar_t__,int,unsigned int,int /*<<< orphan*/ ) ; 
 int none ; 
 scalar_t__ operand_subword_force (scalar_t__,int,int) ; 
 scalar_t__ plus_constant (scalar_t__,int) ; 
 scalar_t__ push_block (scalar_t__,int,int) ; 
 scalar_t__ reg_mentioned_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_mem_align (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  sub_optab ; 
 int upward ; 
 scalar_t__ validize_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtual_outgoing_args_rtx ; 
 int /*<<< orphan*/  virtual_stack_dynamic_rtx ; 
 int word_mode ; 

void
emit_push_insn (rtx x, enum machine_mode mode, tree type, rtx size,
		unsigned int align, int partial, rtx reg, int extra,
		rtx args_addr, rtx args_so_far, int reg_parm_stack_space,
		rtx alignment_pad)
{
  rtx xinner;
  enum direction stack_direction
#ifdef STACK_GROWS_DOWNWARD
    = downward;
#else
    = upward;
#endif

  /* Decide where to pad the argument: `downward' for below,
     `upward' for above, or `none' for don't pad it.
     Default is below for small data on big-endian machines; else above.  */
  enum direction where_pad = FUNCTION_ARG_PADDING (mode, type);

  /* Invert direction if stack is post-decrement.
     FIXME: why?  */
  if (STACK_PUSH_CODE == POST_DEC)
    if (where_pad != none)
      where_pad = (where_pad == downward ? upward : downward);

  xinner = x;

  if (mode == BLKmode)
    {
      /* Copy a block into the stack, entirely or partially.  */

      rtx temp;
      int used;
      int offset;
      int skip;

      offset = partial % (PARM_BOUNDARY / BITS_PER_UNIT);
      used = partial - offset;

      gcc_assert (size);

      /* USED is now the # of bytes we need not copy to the stack
	 because registers will take care of them.  */

      if (partial != 0)
	xinner = adjust_address (xinner, BLKmode, used);

      /* If the partial register-part of the arg counts in its stack size,
	 skip the part of stack space corresponding to the registers.
	 Otherwise, start copying to the beginning of the stack space,
	 by setting SKIP to 0.  */
      skip = (reg_parm_stack_space == 0) ? 0 : used;

#ifdef PUSH_ROUNDING
      /* Do it with several push insns if that doesn't take lots of insns
	 and if there is no difficulty with push insns that skip bytes
	 on the stack for alignment purposes.  */
      if (args_addr == 0
	  && PUSH_ARGS
	  && GET_CODE (size) == CONST_INT
	  && skip == 0
	  && MEM_ALIGN (xinner) >= align
	  && (MOVE_BY_PIECES_P ((unsigned) INTVAL (size) - used, align))
	  /* Here we avoid the case of a structure whose weak alignment
	     forces many pushes of a small amount of data,
	     and such small pushes do rounding that causes trouble.  */
	  && ((! SLOW_UNALIGNED_ACCESS (word_mode, align))
	      || align >= BIGGEST_ALIGNMENT
	      || (PUSH_ROUNDING (align / BITS_PER_UNIT)
		  == (align / BITS_PER_UNIT)))
	  && PUSH_ROUNDING (INTVAL (size)) == INTVAL (size))
	{
	  /* Push padding now if padding above and stack grows down,
	     or if padding below and stack grows up.
	     But if space already allocated, this has already been done.  */
	  if (extra && args_addr == 0
	      && where_pad != none && where_pad != stack_direction)
	    anti_adjust_stack (GEN_INT (extra));

	  move_by_pieces (NULL, xinner, INTVAL (size) - used, align, 0);
	}
      else
#endif /* PUSH_ROUNDING  */
	{
	  rtx target;

	  /* Otherwise make space on the stack and copy the data
	     to the address of that space.  */

	  /* Deduct words put into registers from the size we must copy.  */
	  if (partial != 0)
	    {
	      if (GET_CODE (size) == CONST_INT)
		size = GEN_INT (INTVAL (size) - used);
	      else
		size = expand_binop (GET_MODE (size), sub_optab, size,
				     GEN_INT (used), NULL_RTX, 0,
				     OPTAB_LIB_WIDEN);
	    }

	  /* Get the address of the stack space.
	     In this case, we do not deal with EXTRA separately.
	     A single stack adjust will do.  */
	  if (! args_addr)
	    {
	      temp = push_block (size, extra, where_pad == downward);
	      extra = 0;
	    }
	  else if (GET_CODE (args_so_far) == CONST_INT)
	    temp = memory_address (BLKmode,
				   plus_constant (args_addr,
						  skip + INTVAL (args_so_far)));
	  else
	    temp = memory_address (BLKmode,
				   plus_constant (gen_rtx_PLUS (Pmode,
								args_addr,
								args_so_far),
						  skip));

	  if (!ACCUMULATE_OUTGOING_ARGS)
	    {
	      /* If the source is referenced relative to the stack pointer,
		 copy it to another register to stabilize it.  We do not need
		 to do this if we know that we won't be changing sp.  */

	      if (reg_mentioned_p (virtual_stack_dynamic_rtx, temp)
		  || reg_mentioned_p (virtual_outgoing_args_rtx, temp))
		temp = copy_to_reg (temp);
	    }

	  target = gen_rtx_MEM (BLKmode, temp);

	  /* We do *not* set_mem_attributes here, because incoming arguments
	     may overlap with sibling call outgoing arguments and we cannot
	     allow reordering of reads from function arguments with stores
	     to outgoing arguments of sibling calls.  We do, however, want
	     to record the alignment of the stack slot.  */
	  /* ALIGN may well be better aligned than TYPE, e.g. due to
	     PARM_BOUNDARY.  Assume the caller isn't lying.  */
	  set_mem_align (target, align);

	  emit_block_move (target, xinner, size, BLOCK_OP_CALL_PARM);
	}
    }
  else if (partial > 0)
    {
      /* Scalar partly in registers.  */

      int size = GET_MODE_SIZE (mode) / UNITS_PER_WORD;
      int i;
      int not_stack;
      /* # bytes of start of argument
	 that we must make space for but need not store.  */
      int offset = partial % (PARM_BOUNDARY / BITS_PER_UNIT);
      int args_offset = INTVAL (args_so_far);
      int skip;

      /* Push padding now if padding above and stack grows down,
	 or if padding below and stack grows up.
	 But if space already allocated, this has already been done.  */
      if (extra && args_addr == 0
	  && where_pad != none && where_pad != stack_direction)
	anti_adjust_stack (GEN_INT (extra));

      /* If we make space by pushing it, we might as well push
	 the real data.  Otherwise, we can leave OFFSET nonzero
	 and leave the space uninitialized.  */
      if (args_addr == 0)
	offset = 0;

      /* Now NOT_STACK gets the number of words that we don't need to
	 allocate on the stack.  Convert OFFSET to words too.  */
      not_stack = (partial - offset) / UNITS_PER_WORD;
      offset /= UNITS_PER_WORD;

      /* If the partial register-part of the arg counts in its stack size,
	 skip the part of stack space corresponding to the registers.
	 Otherwise, start copying to the beginning of the stack space,
	 by setting SKIP to 0.  */
      skip = (reg_parm_stack_space == 0) ? 0 : not_stack;

      if (CONSTANT_P (x) && ! LEGITIMATE_CONSTANT_P (x))
	x = validize_mem (force_const_mem (mode, x));

      /* If X is a hard register in a non-integer mode, copy it into a pseudo;
	 SUBREGs of such registers are not allowed.  */
      if ((REG_P (x) && REGNO (x) < FIRST_PSEUDO_REGISTER
	   && GET_MODE_CLASS (GET_MODE (x)) != MODE_INT))
	x = copy_to_reg (x);

      /* Loop over all the words allocated on the stack for this arg.  */
      /* We can do it by words, because any scalar bigger than a word
	 has a size a multiple of a word.  */
#ifndef PUSH_ARGS_REVERSED
      for (i = not_stack; i < size; i++)
#else
      for (i = size - 1; i >= not_stack; i--)
#endif
	if (i >= not_stack + offset)
	  emit_push_insn (operand_subword_force (x, i, mode),
			  word_mode, NULL_TREE, NULL_RTX, align, 0, NULL_RTX,
			  0, args_addr,
			  GEN_INT (args_offset + ((i - not_stack + skip)
						  * UNITS_PER_WORD)),
			  reg_parm_stack_space, alignment_pad);
    }
  else
    {
      rtx addr;
      rtx dest;

      /* Push padding now if padding above and stack grows down,
	 or if padding below and stack grows up.
	 But if space already allocated, this has already been done.  */
      if (extra && args_addr == 0
	  && where_pad != none && where_pad != stack_direction)
	anti_adjust_stack (GEN_INT (extra));

#ifdef PUSH_ROUNDING
      if (args_addr == 0 && PUSH_ARGS)
	emit_single_push_insn (mode, x, type);
      else
#endif
	{
	  if (GET_CODE (args_so_far) == CONST_INT)
	    addr
	      = memory_address (mode,
				plus_constant (args_addr,
					       INTVAL (args_so_far)));
	  else
	    addr = memory_address (mode, gen_rtx_PLUS (Pmode, args_addr,
						       args_so_far));
	  dest = gen_rtx_MEM (mode, addr);

	  /* We do *not* set_mem_attributes here, because incoming arguments
	     may overlap with sibling call outgoing arguments and we cannot
	     allow reordering of reads from function arguments with stores
	     to outgoing arguments of sibling calls.  We do, however, want
	     to record the alignment of the stack slot.  */
	  /* ALIGN may well be better aligned than TYPE, e.g. due to
	     PARM_BOUNDARY.  Assume the caller isn't lying.  */
	  set_mem_align (dest, align);

	  emit_move_insn (dest, x);
	}
    }

  /* If part should go in registers, copy that part
     into the appropriate registers.  Do this now, at the end,
     since mem-to-mem copies above may do function calls.  */
  if (partial > 0 && reg != 0)
    {
      /* Handle calls that pass values in multiple non-contiguous locations.
	 The Irix 6 ABI has examples of this.  */
      if (GET_CODE (reg) == PARALLEL)
	emit_group_load (reg, x, type, -1);
      else
	{
	  gcc_assert (partial % UNITS_PER_WORD == 0);
	  move_block_to_reg (REGNO (reg), x, partial / UNITS_PER_WORD, mode);
	}
    }

  if (extra && args_addr == 0 && where_pad == stack_direction)
    anti_adjust_stack (GEN_INT (extra));

  if (alignment_pad && args_addr == 0)
    anti_adjust_stack (alignment_pad);
}