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
struct scsi_cmnd {TYPE_1__* device; } ;
struct sbp2_logical_unit {TYPE_2__* tgt; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_id; } ;
struct TYPE_3__ {struct sbp2_logical_unit* hostdata; } ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  fw_notify (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp2_agent_reset (struct sbp2_logical_unit*) ; 
 int /*<<< orphan*/  sbp2_cancel_orbs (struct sbp2_logical_unit*) ; 

__attribute__((used)) static int sbp2_scsi_abort(struct scsi_cmnd *cmd)
{
	struct sbp2_logical_unit *lu = cmd->device->hostdata;

	fw_notify("%s: sbp2_scsi_abort\n", lu->tgt->bus_id);
	sbp2_agent_reset(lu);
	sbp2_cancel_orbs(lu);

	return SUCCESS;
}