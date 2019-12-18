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
struct TYPE_4__ {int nregs; } ;
struct TYPE_6__ {TYPE_1__ args_info; TYPE_2__* machine; } ;
struct TYPE_5__ {scalar_t__ uses_anonymous_args; } ;

/* Variables and functions */
 int LAST_ARG_REGNUM ; 
 int LAST_LO_REGNUM ; 
 int UNITS_PER_WORD ; 
 TYPE_3__* cfun ; 
 int current_function_args_size ; 
 scalar_t__ current_function_pretend_args_size ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * regs_ever_live ; 

__attribute__((used)) static int
thumb_find_work_register (unsigned long pushed_regs_mask)
{
  int reg;

  /* Check the argument registers first as these are call-used.  The
     register allocation order means that sometimes r3 might be used
     but earlier argument registers might not, so check them all.  */
  for (reg = LAST_ARG_REGNUM; reg >= 0; reg --)
    if (!regs_ever_live[reg])
      return reg;

  /* Before going on to check the call-saved registers we can try a couple
     more ways of deducing that r3 is available.  The first is when we are
     pushing anonymous arguments onto the stack and we have less than 4
     registers worth of fixed arguments(*).  In this case r3 will be part of
     the variable argument list and so we can be sure that it will be
     pushed right at the start of the function.  Hence it will be available
     for the rest of the prologue.
     (*): ie current_function_pretend_args_size is greater than 0.  */
  if (cfun->machine->uses_anonymous_args
      && current_function_pretend_args_size > 0)
    return LAST_ARG_REGNUM;

  /* The other case is when we have fixed arguments but less than 4 registers
     worth.  In this case r3 might be used in the body of the function, but
     it is not being used to convey an argument into the function.  In theory
     we could just check current_function_args_size to see how many bytes are
     being passed in argument registers, but it seems that it is unreliable.
     Sometimes it will have the value 0 when in fact arguments are being
     passed.  (See testcase execute/20021111-1.c for an example).  So we also
     check the args_info.nregs field as well.  The problem with this field is
     that it makes no allowances for arguments that are passed to the
     function but which are not used.  Hence we could miss an opportunity
     when a function has an unused argument in r3.  But it is better to be
     safe than to be sorry.  */
  if (! cfun->machine->uses_anonymous_args
      && current_function_args_size >= 0
      && current_function_args_size <= (LAST_ARG_REGNUM * UNITS_PER_WORD)
      && cfun->args_info.nregs < 4)
    return LAST_ARG_REGNUM;

  /* Otherwise look for a call-saved register that is going to be pushed.  */
  for (reg = LAST_LO_REGNUM; reg > LAST_ARG_REGNUM; reg --)
    if (pushed_regs_mask & (1 << reg))
      return reg;

  /* Something went wrong - thumb_compute_save_reg_mask()
     should have arranged for a suitable register to be pushed.  */
  gcc_unreachable ();
}