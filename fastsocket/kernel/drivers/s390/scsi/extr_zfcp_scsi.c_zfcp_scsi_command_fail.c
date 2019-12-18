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
struct zfcp_adapter {int /*<<< orphan*/  dbf; } ;
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* host; } ;
struct TYPE_3__ {scalar_t__* hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_host_byte (struct scsi_cmnd*,int) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_result (char*,int,int /*<<< orphan*/ ,struct scsi_cmnd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zfcp_scsi_command_fail(struct scsi_cmnd *scpnt, int result)
{
	struct zfcp_adapter *adapter =
		(struct zfcp_adapter *) scpnt->device->host->hostdata[0];
	set_host_byte(scpnt, result);
	if ((scpnt->device != NULL) && (scpnt->device->host != NULL))
		zfcp_dbf_scsi_result("fail", 4, adapter->dbf, scpnt, NULL);
	/* return directly */
	scpnt->scsi_done(scpnt);
}