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
struct TYPE_3__ {int /*<<< orphan*/  stack_addr; } ;
struct TYPE_4__ {TYPE_1__ value; } ;
struct frame_info {TYPE_2__ this_id; int /*<<< orphan*/  level; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_debug ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  paddr_nz (int /*<<< orphan*/ ) ; 

void
deprecated_update_frame_base_hack (struct frame_info *frame, CORE_ADDR base)
{
  if (frame_debug)
    fprintf_unfiltered (gdb_stdlog,
			"{ deprecated_update_frame_base_hack (frame=%d,base=0x%s) }\n",
			frame->level, paddr_nz (base));
  /* See comment in "frame.h".  */
  frame->this_id.value.stack_addr = base;
}