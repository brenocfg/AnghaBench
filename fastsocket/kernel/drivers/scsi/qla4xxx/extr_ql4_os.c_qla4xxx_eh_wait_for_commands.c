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
struct scsi_target {int dummy; } ;
struct scsi_qla_host {TYPE_1__* host; } ;
struct scsi_device {int dummy; } ;
struct scsi_cmnd {struct scsi_device* device; } ;
struct TYPE_2__ {int can_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla4xxx_eh_wait_on_command (struct scsi_qla_host*,struct scsi_cmnd*) ; 
 struct scsi_cmnd* scsi_host_find_tag (TYPE_1__*,int) ; 
 struct scsi_target* scsi_target (struct scsi_device*) ; 

__attribute__((used)) static int qla4xxx_eh_wait_for_commands(struct scsi_qla_host *ha,
					struct scsi_target *stgt,
					struct scsi_device *sdev)
{
	int cnt;
	int status = 0;
	struct scsi_cmnd *cmd;

	/*
	 * Waiting for all commands for the designated target or dev
	 * in the active array
	 */
	for (cnt = 0; cnt < ha->host->can_queue; cnt++) {
		cmd = scsi_host_find_tag(ha->host, cnt);
		if (cmd && stgt == scsi_target(cmd->device) &&
		    (!sdev || sdev == cmd->device)) {
			if (!qla4xxx_eh_wait_on_command(ha, cmd)) {
				status++;
				break;
			}
		}
	}
	return status;
}