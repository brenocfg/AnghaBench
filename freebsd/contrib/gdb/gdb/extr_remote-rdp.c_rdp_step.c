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
struct TYPE_2__ {scalar_t__ can_step; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_PC_REGNUM ; 
 int /*<<< orphan*/  RDP_STEP ; 
 int /*<<< orphan*/  arm_get_next_pc (int /*<<< orphan*/ ) ; 
 TYPE_1__ ds ; 
 int /*<<< orphan*/  rdp_execute () ; 
 int /*<<< orphan*/  read_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_rdp_insert_breakpoint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  remote_rdp_remove_breakpoint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void
rdp_step (void)
{
  if (ds.can_step && 0)
    {
      /* The pie board can't do steps so I can't test this, and
         the other code will always work. */
      int status;
      send_rdp ("bbw-S-B",
		RDP_STEP, 0, 1,
		&status);
    }
  else
    {
      char handle[4];
      CORE_ADDR pc = read_register (ARM_PC_REGNUM);
      pc = arm_get_next_pc (pc);
      remote_rdp_insert_breakpoint (pc, handle);
      rdp_execute ();
      remote_rdp_remove_breakpoint (pc, handle);
    }
}