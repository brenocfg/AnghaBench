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
struct frame_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ NORMAL_FRAME ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 
 struct frame_info* get_next_frame (struct frame_info*) ; 

__attribute__((used)) static int
pc_notcurrent (struct frame_info *frame)
{
  /* If FRAME is not the innermost frame, that normally means that
     FRAME->pc points at the return instruction (which is *after* the
     call instruction), and we want to get the line containing the
     call (because the call is where the user thinks the program is).
     However, if the next frame is either a SIGTRAMP_FRAME or a
     DUMMY_FRAME, then the next frame will contain a saved interrupt
     PC and such a PC indicates the current (rather than next)
     instruction/line, consequently, for such cases, want to get the
     line containing fi->pc.  */
  struct frame_info *next = get_next_frame (frame);
  int notcurrent = (next != NULL && get_frame_type (next) == NORMAL_FRAME);
  return notcurrent;
}