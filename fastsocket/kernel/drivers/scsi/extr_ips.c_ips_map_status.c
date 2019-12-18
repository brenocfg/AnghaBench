#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ips_stat_t ;
struct TYPE_16__ {int* sense_info; int /*<<< orphan*/  transfer_length; } ;
struct TYPE_14__ {int /*<<< orphan*/  op_code; } ;
struct TYPE_15__ {TYPE_2__ dcdb; } ;
struct TYPE_17__ {int basic_status; scalar_t__ extended_status; TYPE_9__* scsi_cmd; TYPE_4__ dcdb; TYPE_3__ cmd; scalar_t__ bus; int /*<<< orphan*/  data_len; } ;
typedef  TYPE_5__ ips_scb_t ;
struct TYPE_18__ {int /*<<< orphan*/  host_num; } ;
typedef  TYPE_6__ ips_ha_t ;
typedef  int /*<<< orphan*/  inquiryData ;
struct TYPE_21__ {int result; int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/ * cmnd; TYPE_1__* device; } ;
struct TYPE_20__ {int* sense_info; int /*<<< orphan*/  transfer_length; } ;
struct TYPE_19__ {int DeviceType; } ;
struct TYPE_13__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
typedef  TYPE_7__ IPS_SCSI_INQ_DATA ;
typedef  TYPE_8__ IPS_DCDB_TABLE_TAPE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_VAR (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int,int,int) ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DID_RESET ; 
 int DID_TIME_OUT ; 
 int /*<<< orphan*/  INQUIRY ; 
#define  IPS_CMD_CMPLT_WERROR 140 
 int /*<<< orphan*/  IPS_CMD_EXTENDED_DCDB ; 
 int /*<<< orphan*/  IPS_CMD_EXTENDED_DCDB_SG ; 
#define  IPS_CMD_TIMEOUT 139 
#define  IPS_ERR_CKCOND 138 
#define  IPS_ERR_DEV_RESET 137 
#define  IPS_ERR_HOST_RESET 136 
#define  IPS_ERR_OU_RUN 135 
#define  IPS_ERR_RECOVERY 134 
#define  IPS_ERR_SEL_TO 133 
 int IPS_GSC_STATUS_MASK ; 
#define  IPS_INVAL_CMD_BLK 132 
#define  IPS_INVAL_OPCO 131 
#define  IPS_INVAL_PARM_BLK 130 
#define  IPS_LD_ERROR 129 
#define  IPS_PHYS_DRV_ERROR 128 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int TYPE_DISK ; 
 int /*<<< orphan*/  ips_name ; 
 int /*<<< orphan*/  ips_scmd_buf_read (TYPE_9__*,TYPE_7__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ips_map_status(ips_ha_t * ha, ips_scb_t * scb, ips_stat_t * sp)
{
	int errcode;
	int device_error;
	uint32_t transfer_len;
	IPS_DCDB_TABLE_TAPE *tapeDCDB;
	IPS_SCSI_INQ_DATA inquiryData;

	METHOD_TRACE("ips_map_status", 1);

	if (scb->bus) {
		DEBUG_VAR(2,
			  "(%s%d) Physical device error (%d %d %d): %x %x, Sense Key: %x, ASC: %x, ASCQ: %x",
			  ips_name, ha->host_num,
			  scb->scsi_cmd->device->channel,
			  scb->scsi_cmd->device->id, scb->scsi_cmd->device->lun,
			  scb->basic_status, scb->extended_status,
			  scb->extended_status ==
			  IPS_ERR_CKCOND ? scb->dcdb.sense_info[2] & 0xf : 0,
			  scb->extended_status ==
			  IPS_ERR_CKCOND ? scb->dcdb.sense_info[12] : 0,
			  scb->extended_status ==
			  IPS_ERR_CKCOND ? scb->dcdb.sense_info[13] : 0);
	}

	/* default driver error */
	errcode = DID_ERROR;
	device_error = 0;

	switch (scb->basic_status & IPS_GSC_STATUS_MASK) {
	case IPS_CMD_TIMEOUT:
		errcode = DID_TIME_OUT;
		break;

	case IPS_INVAL_OPCO:
	case IPS_INVAL_CMD_BLK:
	case IPS_INVAL_PARM_BLK:
	case IPS_LD_ERROR:
	case IPS_CMD_CMPLT_WERROR:
		break;

	case IPS_PHYS_DRV_ERROR:
		switch (scb->extended_status) {
		case IPS_ERR_SEL_TO:
			if (scb->bus)
				errcode = DID_NO_CONNECT;

			break;

		case IPS_ERR_OU_RUN:
			if ((scb->cmd.dcdb.op_code == IPS_CMD_EXTENDED_DCDB) ||
			    (scb->cmd.dcdb.op_code ==
			     IPS_CMD_EXTENDED_DCDB_SG)) {
				tapeDCDB = (IPS_DCDB_TABLE_TAPE *) & scb->dcdb;
				transfer_len = tapeDCDB->transfer_length;
			} else {
				transfer_len =
				    (uint32_t) scb->dcdb.transfer_length;
			}

			if ((scb->bus) && (transfer_len < scb->data_len)) {
				/* Underrun - set default to no error */
				errcode = DID_OK;

				/* Restrict access to physical DASD */
				if (scb->scsi_cmd->cmnd[0] == INQUIRY) {
				    ips_scmd_buf_read(scb->scsi_cmd,
                                      &inquiryData, sizeof (inquiryData));
 				    if ((inquiryData.DeviceType & 0x1f) == TYPE_DISK) {
				        errcode = DID_TIME_OUT;
				        break;
				    }
				}
			} else
				errcode = DID_ERROR;

			break;

		case IPS_ERR_RECOVERY:
			/* don't fail recovered errors */
			if (scb->bus)
				errcode = DID_OK;

			break;

		case IPS_ERR_HOST_RESET:
		case IPS_ERR_DEV_RESET:
			errcode = DID_RESET;
			break;

		case IPS_ERR_CKCOND:
			if (scb->bus) {
				if ((scb->cmd.dcdb.op_code ==
				     IPS_CMD_EXTENDED_DCDB)
				    || (scb->cmd.dcdb.op_code ==
					IPS_CMD_EXTENDED_DCDB_SG)) {
					tapeDCDB =
					    (IPS_DCDB_TABLE_TAPE *) & scb->dcdb;
					memcpy(scb->scsi_cmd->sense_buffer,
					       tapeDCDB->sense_info,
					       SCSI_SENSE_BUFFERSIZE);
				} else {
					memcpy(scb->scsi_cmd->sense_buffer,
					       scb->dcdb.sense_info,
					       SCSI_SENSE_BUFFERSIZE);
				}
				device_error = 2;	/* check condition */
			}

			errcode = DID_OK;

			break;

		default:
			errcode = DID_ERROR;
			break;

		}		/* end switch */
	}			/* end switch */

	scb->scsi_cmd->result = device_error | (errcode << 16);

	return (1);
}