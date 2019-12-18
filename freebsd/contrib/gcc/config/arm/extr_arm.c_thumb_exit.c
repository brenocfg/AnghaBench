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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ARG_REGISTER (int) ; 
 int /*<<< orphan*/  ARM_EH_STACKADJ_REGNUM ; 
 int ARM_HARD_FRAME_POINTER_REGNUM ; 
 int DECL_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RESULT (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int GET_MODE (scalar_t__) ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  IP_REGNUM ; 
 int LAST_ARG_REGNUM ; 
 int LR_REGNUM ; 
 int PC_REGNUM ; 
 int SP_REGNUM ; 
 scalar_t__ TARGET_BACKTRACE ; 
 int /*<<< orphan*/  TARGET_INTERWORK ; 
 int TRUE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ *,char*,int,...) ; 
 scalar_t__ current_function_calls_eh_return ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ current_function_return_rtx ; 
 int /*<<< orphan*/  is_called_in_ARM_mode (int /*<<< orphan*/ ) ; 
 int number_of_first_bit_set (unsigned int) ; 
 int /*<<< orphan*/  thumb_pushpop (int /*<<< orphan*/ *,unsigned int,int,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
thumb_exit (FILE *f, int reg_containing_return_addr)
{
  unsigned regs_available_for_popping;
  unsigned regs_to_pop;
  int pops_needed;
  unsigned available;
  unsigned required;
  int mode;
  int size;
  int restore_a4 = FALSE;

  /* Compute the registers we need to pop.  */
  regs_to_pop = 0;
  pops_needed = 0;

  if (reg_containing_return_addr == -1)
    {
      regs_to_pop |= 1 << LR_REGNUM;
      ++pops_needed;
    }

  if (TARGET_BACKTRACE)
    {
      /* Restore the (ARM) frame pointer and stack pointer.  */
      regs_to_pop |= (1 << ARM_HARD_FRAME_POINTER_REGNUM) | (1 << SP_REGNUM);
      pops_needed += 2;
    }

  /* If there is nothing to pop then just emit the BX instruction and
     return.  */
  if (pops_needed == 0)
    {
      if (current_function_calls_eh_return)
	asm_fprintf (f, "\tadd\t%r, %r\n", SP_REGNUM, ARM_EH_STACKADJ_REGNUM);

      asm_fprintf (f, "\tbx\t%r\n", reg_containing_return_addr);
      return;
    }
  /* Otherwise if we are not supporting interworking and we have not created
     a backtrace structure and the function was not entered in ARM mode then
     just pop the return address straight into the PC.  */
  else if (!TARGET_INTERWORK
	   && !TARGET_BACKTRACE
	   && !is_called_in_ARM_mode (current_function_decl)
	   && !current_function_calls_eh_return)
    {
      asm_fprintf (f, "\tpop\t{%r}\n", PC_REGNUM);
      return;
    }

  /* Find out how many of the (return) argument registers we can corrupt.  */
  regs_available_for_popping = 0;

  /* If returning via __builtin_eh_return, the bottom three registers
     all contain information needed for the return.  */
  if (current_function_calls_eh_return)
    size = 12;
  else
    {
      /* If we can deduce the registers used from the function's
	 return value.  This is more reliable that examining
	 regs_ever_live[] because that will be set if the register is
	 ever used in the function, not just if the register is used
	 to hold a return value.  */

      if (current_function_return_rtx != 0)
	mode = GET_MODE (current_function_return_rtx);
      else
	mode = DECL_MODE (DECL_RESULT (current_function_decl));

      size = GET_MODE_SIZE (mode);

      if (size == 0)
	{
	  /* In a void function we can use any argument register.
	     In a function that returns a structure on the stack
	     we can use the second and third argument registers.  */
	  if (mode == VOIDmode)
	    regs_available_for_popping =
	      (1 << ARG_REGISTER (1))
	      | (1 << ARG_REGISTER (2))
	      | (1 << ARG_REGISTER (3));
	  else
	    regs_available_for_popping =
	      (1 << ARG_REGISTER (2))
	      | (1 << ARG_REGISTER (3));
	}
      else if (size <= 4)
	regs_available_for_popping =
	  (1 << ARG_REGISTER (2))
	  | (1 << ARG_REGISTER (3));
      else if (size <= 8)
	regs_available_for_popping =
	  (1 << ARG_REGISTER (3));
    }

  /* Match registers to be popped with registers into which we pop them.  */
  for (available = regs_available_for_popping,
       required  = regs_to_pop;
       required != 0 && available != 0;
       available &= ~(available & - available),
       required  &= ~(required  & - required))
    -- pops_needed;

  /* If we have any popping registers left over, remove them.  */
  if (available > 0)
    regs_available_for_popping &= ~available;

  /* Otherwise if we need another popping register we can use
     the fourth argument register.  */
  else if (pops_needed)
    {
      /* If we have not found any free argument registers and
	 reg a4 contains the return address, we must move it.  */
      if (regs_available_for_popping == 0
	  && reg_containing_return_addr == LAST_ARG_REGNUM)
	{
	  asm_fprintf (f, "\tmov\t%r, %r\n", LR_REGNUM, LAST_ARG_REGNUM);
	  reg_containing_return_addr = LR_REGNUM;
	}
      else if (size > 12)
	{
	  /* Register a4 is being used to hold part of the return value,
	     but we have dire need of a free, low register.  */
	  restore_a4 = TRUE;

	  asm_fprintf (f, "\tmov\t%r, %r\n",IP_REGNUM, LAST_ARG_REGNUM);
	}

      if (reg_containing_return_addr != LAST_ARG_REGNUM)
	{
	  /* The fourth argument register is available.  */
	  regs_available_for_popping |= 1 << LAST_ARG_REGNUM;

	  --pops_needed;
	}
    }

  /* Pop as many registers as we can.  */
  thumb_pushpop (f, regs_available_for_popping, FALSE, NULL,
		 regs_available_for_popping);

  /* Process the registers we popped.  */
  if (reg_containing_return_addr == -1)
    {
      /* The return address was popped into the lowest numbered register.  */
      regs_to_pop &= ~(1 << LR_REGNUM);

      reg_containing_return_addr =
	number_of_first_bit_set (regs_available_for_popping);

      /* Remove this register for the mask of available registers, so that
         the return address will not be corrupted by further pops.  */
      regs_available_for_popping &= ~(1 << reg_containing_return_addr);
    }

  /* If we popped other registers then handle them here.  */
  if (regs_available_for_popping)
    {
      int frame_pointer;

      /* Work out which register currently contains the frame pointer.  */
      frame_pointer = number_of_first_bit_set (regs_available_for_popping);

      /* Move it into the correct place.  */
      asm_fprintf (f, "\tmov\t%r, %r\n",
		   ARM_HARD_FRAME_POINTER_REGNUM, frame_pointer);

      /* (Temporarily) remove it from the mask of popped registers.  */
      regs_available_for_popping &= ~(1 << frame_pointer);
      regs_to_pop &= ~(1 << ARM_HARD_FRAME_POINTER_REGNUM);

      if (regs_available_for_popping)
	{
	  int stack_pointer;

	  /* We popped the stack pointer as well,
	     find the register that contains it.  */
	  stack_pointer = number_of_first_bit_set (regs_available_for_popping);

	  /* Move it into the stack register.  */
	  asm_fprintf (f, "\tmov\t%r, %r\n", SP_REGNUM, stack_pointer);

	  /* At this point we have popped all necessary registers, so
	     do not worry about restoring regs_available_for_popping
	     to its correct value:

	     assert (pops_needed == 0)
	     assert (regs_available_for_popping == (1 << frame_pointer))
	     assert (regs_to_pop == (1 << STACK_POINTER))  */
	}
      else
	{
	  /* Since we have just move the popped value into the frame
	     pointer, the popping register is available for reuse, and
	     we know that we still have the stack pointer left to pop.  */
	  regs_available_for_popping |= (1 << frame_pointer);
	}
    }

  /* If we still have registers left on the stack, but we no longer have
     any registers into which we can pop them, then we must move the return
     address into the link register and make available the register that
     contained it.  */
  if (regs_available_for_popping == 0 && pops_needed > 0)
    {
      regs_available_for_popping |= 1 << reg_containing_return_addr;

      asm_fprintf (f, "\tmov\t%r, %r\n", LR_REGNUM,
		   reg_containing_return_addr);

      reg_containing_return_addr = LR_REGNUM;
    }

  /* If we have registers left on the stack then pop some more.
     We know that at most we will want to pop FP and SP.  */
  if (pops_needed > 0)
    {
      int  popped_into;
      int  move_to;

      thumb_pushpop (f, regs_available_for_popping, FALSE, NULL,
		     regs_available_for_popping);

      /* We have popped either FP or SP.
	 Move whichever one it is into the correct register.  */
      popped_into = number_of_first_bit_set (regs_available_for_popping);
      move_to     = number_of_first_bit_set (regs_to_pop);

      asm_fprintf (f, "\tmov\t%r, %r\n", move_to, popped_into);

      regs_to_pop &= ~(1 << move_to);

      --pops_needed;
    }

  /* If we still have not popped everything then we must have only
     had one register available to us and we are now popping the SP.  */
  if (pops_needed > 0)
    {
      int  popped_into;

      thumb_pushpop (f, regs_available_for_popping, FALSE, NULL,
		     regs_available_for_popping);

      popped_into = number_of_first_bit_set (regs_available_for_popping);

      asm_fprintf (f, "\tmov\t%r, %r\n", SP_REGNUM, popped_into);
      /*
	assert (regs_to_pop == (1 << STACK_POINTER))
	assert (pops_needed == 1)
      */
    }

  /* If necessary restore the a4 register.  */
  if (restore_a4)
    {
      if (reg_containing_return_addr != LR_REGNUM)
	{
	  asm_fprintf (f, "\tmov\t%r, %r\n", LR_REGNUM, LAST_ARG_REGNUM);
	  reg_containing_return_addr = LR_REGNUM;
	}

      asm_fprintf (f, "\tmov\t%r, %r\n", LAST_ARG_REGNUM, IP_REGNUM);
    }

  if (current_function_calls_eh_return)
    asm_fprintf (f, "\tadd\t%r, %r\n", SP_REGNUM, ARM_EH_STACKADJ_REGNUM);

  /* Return to caller.  */
  asm_fprintf (f, "\tbx\t%r\n", reg_containing_return_addr);
}