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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IP_REGNUM ; 
 scalar_t__ IS_NAKED (int /*<<< orphan*/ ) ; 
 int LAST_ARG_REGNUM ; 
 int LAST_LO_REGNUM ; 
 int LR_REGNUM ; 
 int PC_REGNUM ; 
 int /*<<< orphan*/  SP_REGNUM ; 
 scalar_t__ TARGET_BACKTRACE ; 
 int /*<<< orphan*/  arm_current_func_type () ; 
 int arm_size_return_regs () ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int bit_count (unsigned long) ; 
 scalar_t__ current_function_pretend_args_size ; 
 int /*<<< orphan*/  internal_error (char*) ; 
 scalar_t__ return_used_this_function ; 
 unsigned long thumb_compute_save_reg_mask () ; 
 int /*<<< orphan*/  thumb_exit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  thumb_pushpop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

const char *
thumb_unexpanded_epilogue (void)
{
  int regno;
  unsigned long live_regs_mask = 0;
  int high_regs_pushed = 0;
  int had_to_push_lr;
  int size;

  if (return_used_this_function)
    return "";

  if (IS_NAKED (arm_current_func_type ()))
    return "";

  live_regs_mask = thumb_compute_save_reg_mask ();
  high_regs_pushed = bit_count (live_regs_mask & 0x0f00);

  /* If we can deduce the registers used from the function's return value.
     This is more reliable that examining regs_ever_live[] because that
     will be set if the register is ever used in the function, not just if
     the register is used to hold a return value.  */
  size = arm_size_return_regs ();

  /* The prolog may have pushed some high registers to use as
     work registers.  e.g. the testsuite file:
     gcc/testsuite/gcc/gcc.c-torture/execute/complex-2.c
     compiles to produce:
	push	{r4, r5, r6, r7, lr}
	mov	r7, r9
	mov	r6, r8
	push	{r6, r7}
     as part of the prolog.  We have to undo that pushing here.  */

  if (high_regs_pushed)
    {
      unsigned long mask = live_regs_mask & 0xff;
      int next_hi_reg;

      /* The available low registers depend on the size of the value we are
         returning.  */
      if (size <= 12)
	mask |=  1 << 3;
      if (size <= 8)
	mask |= 1 << 2;

      if (mask == 0)
	/* Oh dear!  We have no low registers into which we can pop
           high registers!  */
	internal_error
	  ("no low registers available for popping high registers");

      for (next_hi_reg = 8; next_hi_reg < 13; next_hi_reg++)
	if (live_regs_mask & (1 << next_hi_reg))
	  break;

      while (high_regs_pushed)
	{
	  /* Find lo register(s) into which the high register(s) can
             be popped.  */
	  for (regno = 0; regno <= LAST_LO_REGNUM; regno++)
	    {
	      if (mask & (1 << regno))
		high_regs_pushed--;
	      if (high_regs_pushed == 0)
		break;
	    }

	  mask &= (2 << regno) - 1;	/* A noop if regno == 8 */

	  /* Pop the values into the low register(s).  */
	  thumb_pushpop (asm_out_file, mask, 0, NULL, mask);

	  /* Move the value(s) into the high registers.  */
	  for (regno = 0; regno <= LAST_LO_REGNUM; regno++)
	    {
	      if (mask & (1 << regno))
		{
		  asm_fprintf (asm_out_file, "\tmov\t%r, %r\n", next_hi_reg,
			       regno);

		  for (next_hi_reg++; next_hi_reg < 13; next_hi_reg++)
		    if (live_regs_mask & (1 << next_hi_reg))
		      break;
		}
	    }
	}
      live_regs_mask &= ~0x0f00;
    }

  had_to_push_lr = (live_regs_mask & (1 << LR_REGNUM)) != 0;
  live_regs_mask &= 0xff;

  if (current_function_pretend_args_size == 0 || TARGET_BACKTRACE)
    {
      /* Pop the return address into the PC.  */
      if (had_to_push_lr)
	live_regs_mask |= 1 << PC_REGNUM;

      /* Either no argument registers were pushed or a backtrace
	 structure was created which includes an adjusted stack
	 pointer, so just pop everything.  */
      if (live_regs_mask)
	thumb_pushpop (asm_out_file, live_regs_mask, FALSE, NULL,
		       live_regs_mask);

      /* We have either just popped the return address into the
	 PC or it is was kept in LR for the entire function.  */
      if (!had_to_push_lr)
	thumb_exit (asm_out_file, LR_REGNUM);
    }
  else
    {
      /* Pop everything but the return address.  */
      if (live_regs_mask)
	thumb_pushpop (asm_out_file, live_regs_mask, FALSE, NULL,
		       live_regs_mask);

      if (had_to_push_lr)
	{
	  if (size > 12)
	    {
	      /* We have no free low regs, so save one.  */
	      asm_fprintf (asm_out_file, "\tmov\t%r, %r\n", IP_REGNUM,
			   LAST_ARG_REGNUM);
	    }

	  /* Get the return address into a temporary register.  */
	  thumb_pushpop (asm_out_file, 1 << LAST_ARG_REGNUM, 0, NULL,
			 1 << LAST_ARG_REGNUM);

	  if (size > 12)
	    {
	      /* Move the return address to lr.  */
	      asm_fprintf (asm_out_file, "\tmov\t%r, %r\n", LR_REGNUM,
			   LAST_ARG_REGNUM);
	      /* Restore the low register.  */
	      asm_fprintf (asm_out_file, "\tmov\t%r, %r\n", LAST_ARG_REGNUM,
			   IP_REGNUM);
	      regno = LR_REGNUM;
	    }
	  else
	    regno = LAST_ARG_REGNUM;
	}
      else
	regno = LR_REGNUM;

      /* Remove the argument registers that were pushed onto the stack.  */
      asm_fprintf (asm_out_file, "\tadd\t%r, %r, #%d\n",
		   SP_REGNUM, SP_REGNUM,
		   current_function_pretend_args_size);

      thumb_exit (asm_out_file, regno);
    }

  return "";
}