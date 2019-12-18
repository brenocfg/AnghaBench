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
typedef  int u32 ;
struct megasas_instance {int dummy; } ;
struct megasas_header {int cmd_status; } ;
struct megasas_cmd {TYPE_1__* frame; } ;
struct TYPE_2__ {struct megasas_header hdr; } ;

/* Variables and functions */
 int ETIME ; 
 int MFI_POLL_TIMEOUT_SECS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rmb () ; 

int
wait_and_poll(struct megasas_instance *instance, struct megasas_cmd *cmd)
{
	int i;
	struct megasas_header *frame_hdr = &cmd->frame->hdr;

	u32 msecs = MFI_POLL_TIMEOUT_SECS * 1000;

	/*
	 * Wait for cmd_status to change
	 */
	for (i = 0; (i < msecs) && (frame_hdr->cmd_status == 0xff); i += 20) {
		rmb();
		msleep(20);
	}

	if (frame_hdr->cmd_status == 0xff)
		return -ETIME;

	return 0;
}