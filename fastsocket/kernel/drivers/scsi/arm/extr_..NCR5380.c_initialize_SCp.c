#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ length; } ;
struct TYPE_9__ {scalar_t__ this_residual; int /*<<< orphan*/ * ptr; scalar_t__ buffers_residual; TYPE_3__* buffer; } ;
struct TYPE_10__ {TYPE_1__ SCp; } ;
typedef  TYPE_2__ Scsi_Cmnd ;

/* Variables and functions */
 scalar_t__ scsi_bufflen (TYPE_2__*) ; 
 scalar_t__ scsi_sg_count (TYPE_2__*) ; 
 TYPE_3__* scsi_sglist (TYPE_2__*) ; 
 int /*<<< orphan*/ * sg_virt (TYPE_3__*) ; 

__attribute__((used)) static __inline__ void initialize_SCp(Scsi_Cmnd * cmd)
{
	/* 
	 * Initialize the Scsi Pointer field so that all of the commands in the 
	 * various queues are valid.
	 */

	if (scsi_bufflen(cmd)) {
		cmd->SCp.buffer = scsi_sglist(cmd);
		cmd->SCp.buffers_residual = scsi_sg_count(cmd) - 1;
		cmd->SCp.ptr = sg_virt(cmd->SCp.buffer);
		cmd->SCp.this_residual = cmd->SCp.buffer->length;
	} else {
		cmd->SCp.buffer = NULL;
		cmd->SCp.buffers_residual = 0;
		cmd->SCp.ptr = NULL;
		cmd->SCp.this_residual = 0;
	}
}