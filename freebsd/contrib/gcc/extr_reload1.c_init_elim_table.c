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
struct elim_table_1 {scalar_t__ from; scalar_t__ to; } ;
struct elim_table {scalar_t__ from; scalar_t__ to; int can_eliminate; int can_eliminate_previous; void* to_rtx; void* from_rtx; } ;

/* Variables and functions */
 scalar_t__ CAN_ELIMINATE (scalar_t__,scalar_t__) ; 
 scalar_t__ EXIT_IGNORE_STACK ; 
 scalar_t__ FRAME_POINTER_REQUIRED ; 
 size_t NUM_ELIMINABLE_REGS ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ STACK_POINTER_REGNUM ; 
 scalar_t__ current_function_accesses_prior_frames ; 
 scalar_t__ current_function_calls_alloca ; 
 int /*<<< orphan*/  flag_omit_frame_pointer ; 
 int frame_pointer_needed ; 
 void* gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ num_eliminable ; 
 struct elim_table* reg_eliminate ; 
 struct elim_table_1* reg_eliminate_1 ; 
 struct elim_table* xcalloc (int,size_t) ; 

__attribute__((used)) static void
init_elim_table (void)
{
  struct elim_table *ep;
#ifdef ELIMINABLE_REGS
  const struct elim_table_1 *ep1;
#endif

  if (!reg_eliminate)
    reg_eliminate = xcalloc (sizeof (struct elim_table), NUM_ELIMINABLE_REGS);

  /* Does this function require a frame pointer?  */

  frame_pointer_needed = (! flag_omit_frame_pointer
			  /* ?? If EXIT_IGNORE_STACK is set, we will not save
			     and restore sp for alloca.  So we can't eliminate
			     the frame pointer in that case.  At some point,
			     we should improve this by emitting the
			     sp-adjusting insns for this case.  */
			  || (current_function_calls_alloca
			      && EXIT_IGNORE_STACK)
			  || current_function_accesses_prior_frames
			  || FRAME_POINTER_REQUIRED);

  num_eliminable = 0;

#ifdef ELIMINABLE_REGS
  for (ep = reg_eliminate, ep1 = reg_eliminate_1;
       ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++, ep1++)
    {
      ep->from = ep1->from;
      ep->to = ep1->to;
      ep->can_eliminate = ep->can_eliminate_previous
	= (CAN_ELIMINATE (ep->from, ep->to)
	   && ! (ep->to == STACK_POINTER_REGNUM && frame_pointer_needed));
    }
#else
  reg_eliminate[0].from = reg_eliminate_1[0].from;
  reg_eliminate[0].to = reg_eliminate_1[0].to;
  reg_eliminate[0].can_eliminate = reg_eliminate[0].can_eliminate_previous
    = ! frame_pointer_needed;
#endif

  /* Count the number of eliminable registers and build the FROM and TO
     REG rtx's.  Note that code in gen_rtx_REG will cause, e.g.,
     gen_rtx_REG (Pmode, STACK_POINTER_REGNUM) to equal stack_pointer_rtx.
     We depend on this.  */
  for (ep = reg_eliminate; ep < &reg_eliminate[NUM_ELIMINABLE_REGS]; ep++)
    {
      num_eliminable += ep->can_eliminate;
      ep->from_rtx = gen_rtx_REG (Pmode, ep->from);
      ep->to_rtx = gen_rtx_REG (Pmode, ep->to);
    }
}