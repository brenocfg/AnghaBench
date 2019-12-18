#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int object_number; unsigned int interrupt_interval_lsw; unsigned int interrupt_interval_msw; int /*<<< orphan*/  cmd_id; } ;
typedef  TYPE_1__ audpp_cmd_avsync ;
struct TYPE_5__ {int avsync_mask; int* avsync; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDPP_CMD_AVSYNC ; 
 scalar_t__ BAD_ID (int) ; 
 int /*<<< orphan*/  audpp_send_queue1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 TYPE_2__ the_audpp_state ; 

void audpp_avsync(int id, unsigned rate)
{
	unsigned long flags;
	audpp_cmd_avsync cmd;

	if (BAD_ID(id))
		return;

	local_irq_save(flags);
	if (rate)
		the_audpp_state.avsync_mask |= (1 << id);
	else
		the_audpp_state.avsync_mask &= (~(1 << id));
	the_audpp_state.avsync[0] &= the_audpp_state.avsync_mask;
	local_irq_restore(flags);

	cmd.cmd_id = AUDPP_CMD_AVSYNC;
	cmd.object_number = id;
	cmd.interrupt_interval_lsw = rate;
	cmd.interrupt_interval_msw = rate >> 16;
	audpp_send_queue1(&cmd, sizeof(cmd));
}