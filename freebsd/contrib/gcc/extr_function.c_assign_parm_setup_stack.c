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
struct assign_parm_data_one {scalar_t__ promoted_mode; scalar_t__ nominal_mode; scalar_t__ entry_parm; scalar_t__ stack_parm; int /*<<< orphan*/  passed_type; } ;
struct assign_parm_data_all {int /*<<< orphan*/  conversion_insns; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_OP_NORMAL ; 
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DECL_RTL (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 scalar_t__ adjust_address (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ assign_stack_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ convert_to_mode (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_block_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  int_size_in_bytes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_to_sequence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mem_attributes (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  validize_mem (scalar_t__) ; 

__attribute__((used)) static void
assign_parm_setup_stack (struct assign_parm_data_all *all, tree parm,
		         struct assign_parm_data_one *data)
{
  /* Value must be stored in the stack slot STACK_PARM during function
     execution.  */
  bool to_conversion = false;

  if (data->promoted_mode != data->nominal_mode)
    {
      /* Conversion is required.  */
      rtx tempreg = gen_reg_rtx (GET_MODE (data->entry_parm));

      emit_move_insn (tempreg, validize_mem (data->entry_parm));

      push_to_sequence (all->conversion_insns);
      to_conversion = true;

      data->entry_parm = convert_to_mode (data->nominal_mode, tempreg,
					  TYPE_UNSIGNED (TREE_TYPE (parm)));

      if (data->stack_parm)
	/* ??? This may need a big-endian conversion on sparc64.  */
	data->stack_parm
	  = adjust_address (data->stack_parm, data->nominal_mode, 0);
    }

  if (data->entry_parm != data->stack_parm)
    {
      rtx src, dest;

      if (data->stack_parm == 0)
	{
	  data->stack_parm
	    = assign_stack_local (GET_MODE (data->entry_parm),
				  GET_MODE_SIZE (GET_MODE (data->entry_parm)),
				  TYPE_ALIGN (data->passed_type));
	  set_mem_attributes (data->stack_parm, parm, 1);
	}

      dest = validize_mem (data->stack_parm);
      src = validize_mem (data->entry_parm);

      if (MEM_P (src))
	{
	  /* Use a block move to handle potentially misaligned entry_parm.  */
	  if (!to_conversion)
	    push_to_sequence (all->conversion_insns);
	  to_conversion = true;

	  emit_block_move (dest, src,
			   GEN_INT (int_size_in_bytes (data->passed_type)),
			   BLOCK_OP_NORMAL);
	}
      else
	emit_move_insn (dest, src);
    }

  if (to_conversion)
    {
      all->conversion_insns = get_insns ();
      end_sequence ();
    }

  SET_DECL_RTL (parm, data->stack_parm);
}