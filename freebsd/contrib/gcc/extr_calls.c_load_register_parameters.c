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
struct TYPE_2__ {scalar_t__ where_pad; } ;
struct arg_data {scalar_t__ tail_call_reg; scalar_t__ reg; int partial; scalar_t__ value; int n_aligned_regs; scalar_t__* aligned_regs; int /*<<< orphan*/  mode; TYPE_1__ locate; scalar_t__ pass_on_stack; int /*<<< orphan*/  parallel_value; int /*<<< orphan*/  tree_value; } ;
typedef  scalar_t__ rtx ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int BITS_PER_UNIT ; 
 scalar_t__ BLKmode ; 
 scalar_t__ BYTES_BIG_ENDIAN ; 
 int ECF_SIBCALL ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 int LSHIFT_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ REGNO (scalar_t__) ; 
 int RSHIFT_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_sibcall_argument_overlap (scalar_t__,struct arg_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ downward ; 
 int /*<<< orphan*/  emit_group_move (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_shift (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_last_insn () ; 
 int int_size_in_bytes (int /*<<< orphan*/ ) ; 
 scalar_t__ mem_overlaps_already_clobbered_arg_p (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  move_block_to_reg (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ operand_subword_force (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ upward ; 
 int /*<<< orphan*/  use_group_regs (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  use_reg (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  use_regs (scalar_t__*,scalar_t__,int) ; 
 scalar_t__ validize_mem (scalar_t__) ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static void
load_register_parameters (struct arg_data *args, int num_actuals,
			  rtx *call_fusage, int flags, int is_sibcall,
			  int *sibcall_failure)
{
  int i, j;

  for (i = 0; i < num_actuals; i++)
    {
      rtx reg = ((flags & ECF_SIBCALL)
		 ? args[i].tail_call_reg : args[i].reg);
      if (reg)
	{
	  int partial = args[i].partial;
	  int nregs;
	  int size = 0;
	  rtx before_arg = get_last_insn ();
	  /* Set non-negative if we must move a word at a time, even if
	     just one word (e.g, partial == 4 && mode == DFmode).  Set
	     to -1 if we just use a normal move insn.  This value can be
	     zero if the argument is a zero size structure.  */
	  nregs = -1;
	  if (GET_CODE (reg) == PARALLEL)
	    ;
	  else if (partial)
	    {
	      gcc_assert (partial % UNITS_PER_WORD == 0);
	      nregs = partial / UNITS_PER_WORD;
	    }
	  else if (TYPE_MODE (TREE_TYPE (args[i].tree_value)) == BLKmode)
	    {
	      size = int_size_in_bytes (TREE_TYPE (args[i].tree_value));
	      nregs = (size + (UNITS_PER_WORD - 1)) / UNITS_PER_WORD;
	    }
	  else
	    size = GET_MODE_SIZE (args[i].mode);

	  /* Handle calls that pass values in multiple non-contiguous
	     locations.  The Irix 6 ABI has examples of this.  */

	  if (GET_CODE (reg) == PARALLEL)
	    emit_group_move (reg, args[i].parallel_value);

	  /* If simple case, just do move.  If normal partial, store_one_arg
	     has already loaded the register for us.  In all other cases,
	     load the register(s) from memory.  */

	  else if (nregs == -1)
	    {
	      emit_move_insn (reg, args[i].value);
#ifdef BLOCK_REG_PADDING
	      /* Handle case where we have a value that needs shifting
		 up to the msb.  eg. a QImode value and we're padding
		 upward on a BYTES_BIG_ENDIAN machine.  */
	      if (size < UNITS_PER_WORD
		  && (args[i].locate.where_pad
		      == (BYTES_BIG_ENDIAN ? upward : downward)))
		{
		  rtx x;
		  int shift = (UNITS_PER_WORD - size) * BITS_PER_UNIT;

		  /* Assigning REG here rather than a temp makes CALL_FUSAGE
		     report the whole reg as used.  Strictly speaking, the
		     call only uses SIZE bytes at the msb end, but it doesn't
		     seem worth generating rtl to say that.  */
		  reg = gen_rtx_REG (word_mode, REGNO (reg));
		  x = expand_shift (LSHIFT_EXPR, word_mode, reg,
				    build_int_cst (NULL_TREE, shift),
				    reg, 1);
		  if (x != reg)
		    emit_move_insn (reg, x);
		}
#endif
	    }

	  /* If we have pre-computed the values to put in the registers in
	     the case of non-aligned structures, copy them in now.  */

	  else if (args[i].n_aligned_regs != 0)
	    for (j = 0; j < args[i].n_aligned_regs; j++)
	      emit_move_insn (gen_rtx_REG (word_mode, REGNO (reg) + j),
			      args[i].aligned_regs[j]);

	  else if (partial == 0 || args[i].pass_on_stack)
	    {
	      rtx mem = validize_mem (args[i].value);

	      /* Check for overlap with already clobbered argument area.  */
	      if (is_sibcall
		  && mem_overlaps_already_clobbered_arg_p (XEXP (args[i].value, 0),
							   size))
		*sibcall_failure = 1;

	      /* Handle a BLKmode that needs shifting.  */
	      if (nregs == 1 && size < UNITS_PER_WORD
#ifdef BLOCK_REG_PADDING
		  && args[i].locate.where_pad == downward
#else
		  && BYTES_BIG_ENDIAN
#endif
		 )
		{
		  rtx tem = operand_subword_force (mem, 0, args[i].mode);
		  rtx ri = gen_rtx_REG (word_mode, REGNO (reg));
		  rtx x = gen_reg_rtx (word_mode);
		  int shift = (UNITS_PER_WORD - size) * BITS_PER_UNIT;
		  enum tree_code dir = BYTES_BIG_ENDIAN ? RSHIFT_EXPR
							: LSHIFT_EXPR;

		  emit_move_insn (x, tem);
		  x = expand_shift (dir, word_mode, x,
				    build_int_cst (NULL_TREE, shift),
				    ri, 1);
		  if (x != ri)
		    emit_move_insn (ri, x);
		}
	      else
		move_block_to_reg (REGNO (reg), mem, nregs, args[i].mode);
	    }

	  /* When a parameter is a block, and perhaps in other cases, it is
	     possible that it did a load from an argument slot that was
	     already clobbered.  */
	  if (is_sibcall
	      && check_sibcall_argument_overlap (before_arg, &args[i], 0))
	    *sibcall_failure = 1;

	  /* Handle calls that pass values in multiple non-contiguous
	     locations.  The Irix 6 ABI has examples of this.  */
	  if (GET_CODE (reg) == PARALLEL)
	    use_group_regs (call_fusage, reg);
	  else if (nregs == -1)
	    use_reg (call_fusage, reg);
	  else if (nregs > 0)
	    use_regs (call_fusage, REGNO (reg), nregs);
	}
    }
}