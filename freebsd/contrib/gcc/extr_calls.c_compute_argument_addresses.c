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
struct TYPE_3__ {unsigned int constant; } ;
struct TYPE_4__ {unsigned int boundary; scalar_t__ where_pad; TYPE_1__ size; int /*<<< orphan*/  slot_offset; int /*<<< orphan*/  offset; } ;
struct arg_data {scalar_t__ reg; scalar_t__ partial; int mode; void* stack_slot; void* stack; TYPE_2__ locate; int /*<<< orphan*/  tree_value; int /*<<< orphan*/  pass_on_stack; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ARGS_SIZE_RTX (int /*<<< orphan*/ ) ; 
 unsigned int BITS_PER_UNIT ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  GEN_INT (unsigned int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
 int /*<<< orphan*/  MODE_INT ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ downward ; 
 void* gen_rtx_MEM (int,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int mode_for_size (unsigned int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ plus_constant (scalar_t__,int) ; 
 int /*<<< orphan*/  set_mem_alias_set (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_align (void*,unsigned int) ; 
 int /*<<< orphan*/  set_mem_attributes (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_mem_size (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compute_argument_addresses (struct arg_data *args, rtx argblock, int num_actuals)
{
  if (argblock)
    {
      rtx arg_reg = argblock;
      int i, arg_offset = 0;

      if (GET_CODE (argblock) == PLUS)
	arg_reg = XEXP (argblock, 0), arg_offset = INTVAL (XEXP (argblock, 1));

      for (i = 0; i < num_actuals; i++)
	{
	  rtx offset = ARGS_SIZE_RTX (args[i].locate.offset);
	  rtx slot_offset = ARGS_SIZE_RTX (args[i].locate.slot_offset);
	  rtx addr;
	  unsigned int align, boundary;
	  unsigned int units_on_stack = 0;
	  enum machine_mode partial_mode = VOIDmode;

	  /* Skip this parm if it will not be passed on the stack.  */
	  if (! args[i].pass_on_stack
	      && args[i].reg != 0
	      && args[i].partial == 0)
	    continue;

	  if (GET_CODE (offset) == CONST_INT)
	    addr = plus_constant (arg_reg, INTVAL (offset));
	  else
	    addr = gen_rtx_PLUS (Pmode, arg_reg, offset);

	  addr = plus_constant (addr, arg_offset);

	  if (args[i].partial != 0)
	    {
	      /* Only part of the parameter is being passed on the stack.
		 Generate a simple memory reference of the correct size.  */
	      units_on_stack = args[i].locate.size.constant;
	      partial_mode = mode_for_size (units_on_stack * BITS_PER_UNIT,
					    MODE_INT, 1);
	      args[i].stack = gen_rtx_MEM (partial_mode, addr);
	      set_mem_size (args[i].stack, GEN_INT (units_on_stack));
	    }
	  else
	    {
	      args[i].stack = gen_rtx_MEM (args[i].mode, addr);
	      set_mem_attributes (args[i].stack,
				  TREE_TYPE (args[i].tree_value), 1);
	    }
	  align = BITS_PER_UNIT;
	  boundary = args[i].locate.boundary;
	  if (args[i].locate.where_pad != downward)
	    align = boundary;
	  else if (GET_CODE (offset) == CONST_INT)
	    {
	      align = INTVAL (offset) * BITS_PER_UNIT | boundary;
	      align = align & -align;
	    }
	  set_mem_align (args[i].stack, align);

	  if (GET_CODE (slot_offset) == CONST_INT)
	    addr = plus_constant (arg_reg, INTVAL (slot_offset));
	  else
	    addr = gen_rtx_PLUS (Pmode, arg_reg, slot_offset);

	  addr = plus_constant (addr, arg_offset);

	  if (args[i].partial != 0)
	    {
	      /* Only part of the parameter is being passed on the stack.
		 Generate a simple memory reference of the correct size.  */
	      args[i].stack_slot = gen_rtx_MEM (partial_mode, addr);
	      set_mem_size (args[i].stack_slot, GEN_INT (units_on_stack));
	    }
	  else
	    {
	      args[i].stack_slot = gen_rtx_MEM (args[i].mode, addr);
	      set_mem_attributes (args[i].stack_slot,
				  TREE_TYPE (args[i].tree_value), 1);
	    }
	  set_mem_align (args[i].stack_slot, args[i].locate.boundary);

	  /* Function incoming arguments may overlap with sibling call
	     outgoing arguments and we cannot allow reordering of reads
	     from function arguments with stores to outgoing arguments
	     of sibling calls.  */
	  set_mem_alias_set (args[i].stack, 0);
	  set_mem_alias_set (args[i].stack_slot, 0);
	}
    }
}