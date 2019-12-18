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
struct TYPE_2__ {scalar_t__ total_size; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
#define  ARG_POINTER_REGNUM 131 
#define  FRAME_POINTER_REGNUM 130 
#define  HARD_FRAME_POINTER_REGNUM 129 
#define  STACK_POINTER_REGNUM 128 
 TYPE_1__ current_frame_info ; 
 int /*<<< orphan*/  current_function_is_leaf ; 
 scalar_t__ current_function_outgoing_args_size ; 
 scalar_t__ current_function_pretend_args_size ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_frame_size () ; 
 int /*<<< orphan*/  ia64_compute_frame_size (int /*<<< orphan*/ ) ; 

HOST_WIDE_INT
ia64_initial_elimination_offset (int from, int to)
{
  HOST_WIDE_INT offset;

  ia64_compute_frame_size (get_frame_size ());
  switch (from)
    {
    case FRAME_POINTER_REGNUM:
      switch (to)
	{
	case HARD_FRAME_POINTER_REGNUM:
	  if (current_function_is_leaf)
	    offset = -current_frame_info.total_size;
	  else
	    offset = -(current_frame_info.total_size
		       - current_function_outgoing_args_size - 16);
	  break;

	case STACK_POINTER_REGNUM:
	  if (current_function_is_leaf)
	    offset = 0;
	  else
	    offset = 16 + current_function_outgoing_args_size;
	  break;

	default:
	  gcc_unreachable ();
	}
      break;

    case ARG_POINTER_REGNUM:
      /* Arguments start above the 16 byte save area, unless stdarg
	 in which case we store through the 16 byte save area.  */
      switch (to)
	{
	case HARD_FRAME_POINTER_REGNUM:
	  offset = 16 - current_function_pretend_args_size;
	  break;

	case STACK_POINTER_REGNUM:
	  offset = (current_frame_info.total_size
		    + 16 - current_function_pretend_args_size);
	  break;

	default:
	  gcc_unreachable ();
	}
      break;

    default:
      gcc_unreachable ();
    }

  return offset;
}