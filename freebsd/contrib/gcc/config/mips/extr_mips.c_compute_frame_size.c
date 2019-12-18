#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* machine; } ;
struct TYPE_4__ {unsigned int mask; unsigned int fmask; scalar_t__ fp_save_offset; scalar_t__ fp_sp_offset; scalar_t__ gp_save_offset; scalar_t__ gp_sp_offset; scalar_t__ num_fp; scalar_t__ num_gp; int /*<<< orphan*/  initialized; scalar_t__ fp_reg_size; scalar_t__ gp_reg_size; scalar_t__ cprestore_size; scalar_t__ args_size; scalar_t__ var_size; scalar_t__ total_size; } ;
struct TYPE_5__ {scalar_t__ varargs_size; TYPE_1__ frame; int /*<<< orphan*/  global_pointer; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 unsigned int EH_RETURN_DATA_REGNO (unsigned int) ; 
 unsigned int FP_INC ; 
 unsigned int FP_REG_FIRST ; 
 int FP_REG_LAST ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int GP_REG_FIRST ; 
 unsigned int GP_REG_LAST ; 
 unsigned int INVALID_REGNUM ; 
 scalar_t__ MIPS_STACK_ALIGN (scalar_t__) ; 
 scalar_t__ STARTING_FRAME_OFFSET ; 
 unsigned int UNITS_PER_FPREG ; 
 int UNITS_PER_WORD ; 
 TYPE_3__* cfun ; 
 scalar_t__ current_function_calls_alloca ; 
 scalar_t__ current_function_calls_eh_return ; 
 scalar_t__ current_function_is_leaf ; 
 scalar_t__ current_function_outgoing_args_size ; 
 scalar_t__ current_function_pretend_args_size ; 
 int /*<<< orphan*/  gpr_mode ; 
 int /*<<< orphan*/  mips_global_pointer () ; 
 scalar_t__ mips_save_reg_p (unsigned int) ; 
 int /*<<< orphan*/  reload_completed ; 

HOST_WIDE_INT
compute_frame_size (HOST_WIDE_INT size)
{
  unsigned int regno;
  HOST_WIDE_INT total_size;	/* # bytes that the entire frame takes up */
  HOST_WIDE_INT var_size;	/* # bytes that variables take up */
  HOST_WIDE_INT args_size;	/* # bytes that outgoing arguments take up */
  HOST_WIDE_INT cprestore_size; /* # bytes that the cprestore slot takes up */
  HOST_WIDE_INT gp_reg_rounded;	/* # bytes needed to store gp after rounding */
  HOST_WIDE_INT gp_reg_size;	/* # bytes needed to store gp regs */
  HOST_WIDE_INT fp_reg_size;	/* # bytes needed to store fp regs */
  unsigned int mask;		/* mask of saved gp registers */
  unsigned int fmask;		/* mask of saved fp registers */

  cfun->machine->global_pointer = mips_global_pointer ();

  gp_reg_size = 0;
  fp_reg_size = 0;
  mask = 0;
  fmask	= 0;
  var_size = MIPS_STACK_ALIGN (size);
  args_size = current_function_outgoing_args_size;
  cprestore_size = MIPS_STACK_ALIGN (STARTING_FRAME_OFFSET) - args_size;

  /* The space set aside by STARTING_FRAME_OFFSET isn't needed in leaf
     functions.  If the function has local variables, we're committed
     to allocating it anyway.  Otherwise reclaim it here.  */
  if (var_size == 0 && current_function_is_leaf)
    cprestore_size = args_size = 0;

  /* The MIPS 3.0 linker does not like functions that dynamically
     allocate the stack and have 0 for STACK_DYNAMIC_OFFSET, since it
     looks like we are trying to create a second frame pointer to the
     function, so allocate some stack space to make it happy.  */

  if (args_size == 0 && current_function_calls_alloca)
    args_size = 4 * UNITS_PER_WORD;

  total_size = var_size + args_size + cprestore_size;

  /* Calculate space needed for gp registers.  */
  for (regno = GP_REG_FIRST; regno <= GP_REG_LAST; regno++)
    if (mips_save_reg_p (regno))
      {
	gp_reg_size += GET_MODE_SIZE (gpr_mode);
	mask |= 1 << (regno - GP_REG_FIRST);
      }

  /* We need to restore these for the handler.  */
  if (current_function_calls_eh_return)
    {
      unsigned int i;
      for (i = 0; ; ++i)
	{
	  regno = EH_RETURN_DATA_REGNO (i);
	  if (regno == INVALID_REGNUM)
	    break;
	  gp_reg_size += GET_MODE_SIZE (gpr_mode);
	  mask |= 1 << (regno - GP_REG_FIRST);
	}
    }

  /* This loop must iterate over the same space as its companion in
     save_restore_insns.  */
  for (regno = (FP_REG_LAST - FP_INC + 1);
       regno >= FP_REG_FIRST;
       regno -= FP_INC)
    {
      if (mips_save_reg_p (regno))
	{
	  fp_reg_size += FP_INC * UNITS_PER_FPREG;
	  fmask |= ((1 << FP_INC) - 1) << (regno - FP_REG_FIRST);
	}
    }

  gp_reg_rounded = MIPS_STACK_ALIGN (gp_reg_size);
  total_size += gp_reg_rounded + MIPS_STACK_ALIGN (fp_reg_size);

  /* Add in the space required for saving incoming register arguments.  */
  total_size += current_function_pretend_args_size;
  total_size += MIPS_STACK_ALIGN (cfun->machine->varargs_size);

  /* Save other computed information.  */
  cfun->machine->frame.total_size = total_size;
  cfun->machine->frame.var_size = var_size;
  cfun->machine->frame.args_size = args_size;
  cfun->machine->frame.cprestore_size = cprestore_size;
  cfun->machine->frame.gp_reg_size = gp_reg_size;
  cfun->machine->frame.fp_reg_size = fp_reg_size;
  cfun->machine->frame.mask = mask;
  cfun->machine->frame.fmask = fmask;
  cfun->machine->frame.initialized = reload_completed;
  cfun->machine->frame.num_gp = gp_reg_size / UNITS_PER_WORD;
  cfun->machine->frame.num_fp = fp_reg_size / (FP_INC * UNITS_PER_FPREG);

  if (mask)
    {
      HOST_WIDE_INT offset;

      offset = (args_size + cprestore_size + var_size
		+ gp_reg_size - GET_MODE_SIZE (gpr_mode));
      cfun->machine->frame.gp_sp_offset = offset;
      cfun->machine->frame.gp_save_offset = offset - total_size;
    }
  else
    {
      cfun->machine->frame.gp_sp_offset = 0;
      cfun->machine->frame.gp_save_offset = 0;
    }

  if (fmask)
    {
      HOST_WIDE_INT offset;

      offset = (args_size + cprestore_size + var_size
		+ gp_reg_rounded + fp_reg_size
		- FP_INC * UNITS_PER_FPREG);
      cfun->machine->frame.fp_sp_offset = offset;
      cfun->machine->frame.fp_save_offset = offset - total_size;
    }
  else
    {
      cfun->machine->frame.fp_sp_offset = 0;
      cfun->machine->frame.fp_save_offset = 0;
    }

  /* Ok, we're done.  */
  return total_size;
}