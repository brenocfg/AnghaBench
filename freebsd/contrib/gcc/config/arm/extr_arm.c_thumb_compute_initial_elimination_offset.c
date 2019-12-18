#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ soft_frame; scalar_t__ locals_base; scalar_t__ saved_regs; scalar_t__ outgoing_args; scalar_t__ saved_args; } ;
typedef  TYPE_1__ arm_stack_offsets ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
#define  ARG_POINTER_REGNUM 132 
#define  ARM_HARD_FRAME_POINTER_REGNUM 131 
#define  FRAME_POINTER_REGNUM 130 
#define  STACK_POINTER_REGNUM 129 
#define  THUMB_HARD_FRAME_POINTER_REGNUM 128 
 TYPE_1__* arm_get_frame_offsets () ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

HOST_WIDE_INT
thumb_compute_initial_elimination_offset (unsigned int from, unsigned int to)
{
  arm_stack_offsets *offsets;

  offsets = arm_get_frame_offsets ();

  switch (from)
    {
    case ARG_POINTER_REGNUM:
      switch (to)
	{
	case STACK_POINTER_REGNUM:
	  return offsets->outgoing_args - offsets->saved_args;

	case FRAME_POINTER_REGNUM:
	  return offsets->soft_frame - offsets->saved_args;

	case ARM_HARD_FRAME_POINTER_REGNUM:
	  return offsets->saved_regs - offsets->saved_args;

	case THUMB_HARD_FRAME_POINTER_REGNUM:
	  return offsets->locals_base - offsets->saved_args;

	default:
	  gcc_unreachable ();
	}
      break;

    case FRAME_POINTER_REGNUM:
      switch (to)
	{
	case STACK_POINTER_REGNUM:
	  return offsets->outgoing_args - offsets->soft_frame;

	case ARM_HARD_FRAME_POINTER_REGNUM:
	  return offsets->saved_regs - offsets->soft_frame;

	case THUMB_HARD_FRAME_POINTER_REGNUM:
	  return offsets->locals_base - offsets->soft_frame;

	default:
	  gcc_unreachable ();
	}
      break;

    default:
      gcc_unreachable ();
    }
}