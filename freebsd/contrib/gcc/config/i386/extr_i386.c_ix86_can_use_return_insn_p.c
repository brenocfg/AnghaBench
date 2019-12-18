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
struct ix86_frame {scalar_t__ to_allocate; scalar_t__ nregs; } ;

/* Variables and functions */
 int current_function_args_size ; 
 scalar_t__ current_function_pops_args ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  ix86_compute_frame_layout (struct ix86_frame*) ; 
 int /*<<< orphan*/  reload_completed ; 

int
ix86_can_use_return_insn_p (void)
{
  struct ix86_frame frame;

  if (! reload_completed || frame_pointer_needed)
    return 0;

  /* Don't allow more than 32 pop, since that's all we can do
     with one instruction.  */
  if (current_function_pops_args
      && current_function_args_size >= 32768)
    return 0;

  ix86_compute_frame_layout (&frame);
  return frame.to_allocate == 0 && frame.nregs == 0;
}