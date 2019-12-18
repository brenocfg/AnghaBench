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
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ PC_IN_SIGTRAMP (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ SIGCONTEXT_REGISTER_ADDRESS_P () ; 
 struct frame_unwind const arm_sigtramp_unwind ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 

__attribute__((used)) static const struct frame_unwind *
arm_sigtramp_unwind_sniffer (struct frame_info *next_frame)
{
  /* Note: If an ARM PC_IN_SIGTRAMP method ever needs to compare
     against the name of the function, the code below will have to be
     changed to first fetch the name of the function and then pass
     this name to PC_IN_SIGTRAMP.  */

  if (SIGCONTEXT_REGISTER_ADDRESS_P ()
      && PC_IN_SIGTRAMP (frame_pc_unwind (next_frame), (char *) 0))
    return &arm_sigtramp_unwind;

  return NULL;
}