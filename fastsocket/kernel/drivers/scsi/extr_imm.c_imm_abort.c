#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int phase; } ;
struct scsi_cmnd {TYPE_2__ SCp; TYPE_1__* device; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cur_cmd; } ;
typedef  TYPE_3__ imm_struct ;
struct TYPE_5__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int SUCCESS ; 
 TYPE_3__* imm_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imm_abort(struct scsi_cmnd *cmd)
{
	imm_struct *dev = imm_dev(cmd->device->host);
	/*
	 * There is no method for aborting commands since Iomega
	 * have tied the SCSI_MESSAGE line high in the interface
	 */

	switch (cmd->SCp.phase) {
	case 0:		/* Do not have access to parport */
	case 1:		/* Have not connected to interface */
		dev->cur_cmd = NULL;	/* Forget the problem */
		return SUCCESS;
		break;
	default:		/* SCSI command sent, can not abort */
		return FAILED;
		break;
	}
}