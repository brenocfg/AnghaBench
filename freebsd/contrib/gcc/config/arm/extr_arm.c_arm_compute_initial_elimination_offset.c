#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int soft_frame; int saved_args; int frame; int saved_regs; int outgoing_args; } ;
typedef  TYPE_2__ arm_stack_offsets ;
struct TYPE_7__ {TYPE_1__* machine; int /*<<< orphan*/ * static_chain_decl; } ;
struct TYPE_5__ {int /*<<< orphan*/  uses_anonymous_args; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ARG_POINTER_REGNUM 132 
#define  ARM_HARD_FRAME_POINTER_REGNUM 131 
#define  FRAME_POINTER_REGNUM 130 
#define  STACK_POINTER_REGNUM 129 
#define  THUMB_HARD_FRAME_POINTER_REGNUM 128 
 TYPE_2__* arm_get_frame_offsets () ; 
 TYPE_3__* cfun ; 
 int /*<<< orphan*/  frame_pointer_needed ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

HOST_WIDE_INT
arm_compute_initial_elimination_offset (unsigned int from, unsigned int to)
{
  arm_stack_offsets *offsets;

  offsets = arm_get_frame_offsets ();

  /* OK, now we have enough information to compute the distances.
     There must be an entry in these switch tables for each pair
     of registers in ELIMINABLE_REGS, even if some of the entries
     seem to be redundant or useless.  */
  switch (from)
    {
    case ARG_POINTER_REGNUM:
      switch (to)
	{
	case THUMB_HARD_FRAME_POINTER_REGNUM:
	  return 0;

	case FRAME_POINTER_REGNUM:
	  /* This is the reverse of the soft frame pointer
	     to hard frame pointer elimination below.  */
	  return offsets->soft_frame - offsets->saved_args;

	case ARM_HARD_FRAME_POINTER_REGNUM:
	  /* If there is no stack frame then the hard
	     frame pointer and the arg pointer coincide.  */
	  if (offsets->frame == offsets->saved_regs)
	    return 0;
	  /* FIXME:  Not sure about this.  Maybe we should always return 0 ?  */
	  return (frame_pointer_needed
		  && cfun->static_chain_decl != NULL
		  && ! cfun->machine->uses_anonymous_args) ? 4 : 0;

	case STACK_POINTER_REGNUM:
	  /* If nothing has been pushed on the stack at all
	     then this will return -4.  This *is* correct!  */
	  return offsets->outgoing_args - (offsets->saved_args + 4);

	default:
	  gcc_unreachable ();
	}
      gcc_unreachable ();

    case FRAME_POINTER_REGNUM:
      switch (to)
	{
	case THUMB_HARD_FRAME_POINTER_REGNUM:
	  return 0;

	case ARM_HARD_FRAME_POINTER_REGNUM:
	  /* The hard frame pointer points to the top entry in the
	     stack frame.  The soft frame pointer to the bottom entry
	     in the stack frame.  If there is no stack frame at all,
	     then they are identical.  */

	  return offsets->frame - offsets->soft_frame;

	case STACK_POINTER_REGNUM:
	  return offsets->outgoing_args - offsets->soft_frame;

	default:
	  gcc_unreachable ();
	}
      gcc_unreachable ();

    default:
      /* You cannot eliminate from the stack pointer.
	 In theory you could eliminate from the hard frame
	 pointer to the stack pointer, but this will never
	 happen, since if a stack frame is not needed the
	 hard frame pointer will never be used.  */
      gcc_unreachable ();
    }
}