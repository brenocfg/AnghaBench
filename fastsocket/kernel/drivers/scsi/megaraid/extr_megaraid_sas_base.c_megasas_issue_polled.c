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
struct megasas_instance {TYPE_2__* instancet; } ;
struct megasas_header {int cmd_status; int /*<<< orphan*/  flags; } ;
struct megasas_cmd {TYPE_1__* frame; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* issue_dcmd ) (struct megasas_instance*,struct megasas_cmd*) ;} ;
struct TYPE_3__ {struct megasas_header hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFI_FRAME_DONT_POST_IN_REPLY_QUEUE ; 
 int /*<<< orphan*/  stub1 (struct megasas_instance*,struct megasas_cmd*) ; 
 int wait_and_poll (struct megasas_instance*,struct megasas_cmd*) ; 

int
megasas_issue_polled(struct megasas_instance *instance, struct megasas_cmd *cmd)
{

	struct megasas_header *frame_hdr = &cmd->frame->hdr;

	frame_hdr->cmd_status = 0xFF;
	frame_hdr->flags |= MFI_FRAME_DONT_POST_IN_REPLY_QUEUE;

	/*
	 * Issue the frame using inbound queue port
	 */
	instance->instancet->issue_dcmd(instance, cmd);

	/*
	 * Wait for cmd_status to change
	 */
	return wait_and_poll(instance, cmd);
}