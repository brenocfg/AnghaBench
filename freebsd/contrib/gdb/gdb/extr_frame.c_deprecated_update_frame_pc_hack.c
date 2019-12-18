#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct frame_info {TYPE_2__* next; int /*<<< orphan*/  level; } ;
struct TYPE_3__ {int p; int /*<<< orphan*/  value; } ;
struct TYPE_4__ {TYPE_1__ prev_pc; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_debug ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 

void
deprecated_update_frame_pc_hack (struct frame_info *frame, CORE_ADDR pc)
{
  if (frame_debug)
    fprintf_unfiltered (gdb_stdlog,
			"{ deprecated_update_frame_pc_hack (frame=%d,pc=0x%s) }\n",
			frame->level, paddr_nz (pc));
  /* NOTE: cagney/2003-03-11: Some architectures (e.g., Arm) are
     maintaining a locally allocated frame object.  Since such frame's
     are not in the frame chain, it isn't possible to assume that the
     frame has a next.  Sigh.  */
  if (frame->next != NULL)
    {
      /* While we're at it, update this frame's cached PC value, found
	 in the next frame.  Oh for the day when "struct frame_info"
	 is opaque and this hack on hack can just go away.  */
      frame->next->prev_pc.value = pc;
      frame->next->prev_pc.p = 1;
    }
}