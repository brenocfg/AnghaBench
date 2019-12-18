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
struct zfcp_unit {TYPE_2__* port; } ;
struct zfcp_adapter {int dummy; } ;
struct scsi_cmnd {TYPE_1__* device; } ;
struct TYPE_4__ {struct zfcp_adapter* adapter; } ;
struct TYPE_3__ {struct zfcp_unit* hostdata; } ;

/* Variables and functions */
 int SUCCESS ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,struct scsi_cmnd*) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 

__attribute__((used)) static int zfcp_scsi_eh_host_reset_handler(struct scsi_cmnd *scpnt)
{
	struct zfcp_unit *unit = scpnt->device->hostdata;
	struct zfcp_adapter *adapter = unit->port->adapter;
	int ret;

	zfcp_erp_adapter_reopen(adapter, 0, "schrh_1", scpnt);
	zfcp_erp_wait(adapter);
	ret = fc_block_scsi_eh(scpnt);
	if (ret)
		return ret;

	return SUCCESS;
}