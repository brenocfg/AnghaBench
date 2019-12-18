#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ op_code; } ;
struct TYPE_12__ {scalar_t__ op_code; } ;
struct TYPE_16__ {TYPE_4__ flashfw; TYPE_1__ dcdb; } ;
struct TYPE_17__ {int /*<<< orphan*/  scsi_cmd; TYPE_5__ cmd; int /*<<< orphan*/  extended_status; int /*<<< orphan*/  basic_status; int /*<<< orphan*/  dcdb; } ;
typedef  TYPE_6__ ips_scb_t ;
struct TYPE_13__ {int /*<<< orphan*/  dcdb; } ;
struct TYPE_18__ {int /*<<< orphan*/  AdapterType; int /*<<< orphan*/  ExtendedStatus; int /*<<< orphan*/  BasicStatus; TYPE_2__ CoppCP; } ;
typedef  TYPE_7__ ips_passthru_t ;
struct TYPE_19__ {int /*<<< orphan*/  ioctl_datasize; scalar_t__ ioctl_data; TYPE_3__* pcidev; int /*<<< orphan*/  ad_type; int /*<<< orphan*/  host_num; } ;
typedef  TYPE_8__ ips_ha_t ;
struct TYPE_14__ {scalar_t__ device; } ;
typedef  int /*<<< orphan*/  IPS_DCDB_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_VAR (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IPS_CMD_DCDB ; 
 scalar_t__ IPS_CMD_DOWNLOAD ; 
 scalar_t__ IPS_CMD_RW_BIOSFW ; 
 scalar_t__ IPS_DEVICEID_COPPERHEAD ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_free_flash_copperhead (TYPE_8__*) ; 
 int /*<<< orphan*/  ips_name ; 
 int /*<<< orphan*/  ips_scmd_buf_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_sglist (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ips_cleanup_passthru(ips_ha_t * ha, ips_scb_t * scb)
{
	ips_passthru_t *pt;

	METHOD_TRACE("ips_cleanup_passthru", 1);

	if ((!scb) || (!scb->scsi_cmd) || (!scsi_sglist(scb->scsi_cmd))) {
		DEBUG_VAR(1, "(%s%d) couldn't cleanup after passthru",
			  ips_name, ha->host_num);

		return;
	}
	pt = (ips_passthru_t *) ha->ioctl_data;

	/* Copy data back to the user */
	if (scb->cmd.dcdb.op_code == IPS_CMD_DCDB)	/* Copy DCDB Back to Caller's Area */
		memcpy(&pt->CoppCP.dcdb, &scb->dcdb, sizeof (IPS_DCDB_TABLE));

	pt->BasicStatus = scb->basic_status;
	pt->ExtendedStatus = scb->extended_status;
	pt->AdapterType = ha->ad_type;

	if (ha->pcidev->device == IPS_DEVICEID_COPPERHEAD &&
	    (scb->cmd.flashfw.op_code == IPS_CMD_DOWNLOAD ||
	     scb->cmd.flashfw.op_code == IPS_CMD_RW_BIOSFW))
		ips_free_flash_copperhead(ha);

	ips_scmd_buf_write(scb->scsi_cmd, ha->ioctl_data, ha->ioctl_datasize);
}