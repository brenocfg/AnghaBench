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
struct scsi_sense_data {int extra_len; int add_sense_code; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_1__* device; scalar_t__ sense_buffer; } ;
struct ahd_softc {int dummy; } ;
struct TYPE_2__ {int channel; int id; int lun; } ;

/* Variables and functions */
#define  CAM_AUTOSENSE_FAIL 154 
#define  CAM_BDR_SENT 153 
#define  CAM_BUSY 152 
#define  CAM_CCB_LEN_ERR 151 
#define  CAM_CMD_TIMEOUT 150 
#define  CAM_DATA_RUN_ERR 149 
#define  CAM_NO_HBA 148 
#define  CAM_PATH_INVALID 147 
#define  CAM_PROVIDE_FAIL 146 
#define  CAM_REQUEUE_REQ 145 
#define  CAM_REQ_ABORTED 144 
#define  CAM_REQ_CMP 143 
#define  CAM_REQ_CMP_ERR 142 
#define  CAM_REQ_INPROG 141 
#define  CAM_REQ_INVALID 140 
#define  CAM_REQ_TERMIO 139 
#define  CAM_REQ_TOO_BIG 138 
#define  CAM_SCSI_BUS_RESET 137 
#define  CAM_SCSI_STATUS_ERROR 136 
#define  CAM_SEL_TIMEOUT 135 
#define  CAM_SEQUENCE_FAIL 134 
#define  CAM_UA_ABORT 133 
#define  CAM_UNCOR_PARITY 132 
#define  CAM_UNEXP_BUSFREE 131 
#define  CAM_UNREC_HBA_ERROR 130 
 int DID_ABORT ; 
 int DID_BAD_TARGET ; 
 int DID_BUS_BUSY ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_OK ; 
 int DID_PARITY ; 
 int DID_REQUEUE ; 
 int DID_RESET ; 
 int DID_TIME_OUT ; 
 int DRIVER_SENSE ; 
#define  SCSI_STATUS_CHECK_COND 129 
#define  SCSI_STATUS_CMD_TERMINATED 128 
 int ahd_cmd_get_scsi_status (struct scsi_cmnd*) ; 
 int ahd_cmd_get_transaction_status (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  ahd_cmd_set_transaction_status (struct scsi_cmnd*,int) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void
ahd_linux_queue_cmd_complete(struct ahd_softc *ahd, struct scsi_cmnd *cmd)
{
	int status;
	int new_status = DID_OK;
	int do_fallback = 0;
	int scsi_status;

	/*
	 * Map CAM error codes into Linux Error codes.  We
	 * avoid the conversion so that the DV code has the
	 * full error information available when making
	 * state change decisions.
	 */

	status = ahd_cmd_get_transaction_status(cmd);
	switch (status) {
	case CAM_REQ_INPROG:
	case CAM_REQ_CMP:
		new_status = DID_OK;
		break;
	case CAM_AUTOSENSE_FAIL:
		new_status = DID_ERROR;
		/* Fallthrough */
	case CAM_SCSI_STATUS_ERROR:
		scsi_status = ahd_cmd_get_scsi_status(cmd);

		switch(scsi_status) {
		case SCSI_STATUS_CMD_TERMINATED:
		case SCSI_STATUS_CHECK_COND:
			if ((cmd->result >> 24) != DRIVER_SENSE) {
				do_fallback = 1;
			} else {
				struct scsi_sense_data *sense;
				
				sense = (struct scsi_sense_data *)
					cmd->sense_buffer;
				if (sense->extra_len >= 5 &&
				    (sense->add_sense_code == 0x47
				     || sense->add_sense_code == 0x48))
					do_fallback = 1;
			}
			break;
		default:
			break;
		}
		break;
	case CAM_REQ_ABORTED:
		new_status = DID_ABORT;
		break;
	case CAM_BUSY:
		new_status = DID_BUS_BUSY;
		break;
	case CAM_REQ_INVALID:
	case CAM_PATH_INVALID:
		new_status = DID_BAD_TARGET;
		break;
	case CAM_SEL_TIMEOUT:
		new_status = DID_NO_CONNECT;
		break;
	case CAM_SCSI_BUS_RESET:
	case CAM_BDR_SENT:
		new_status = DID_RESET;
		break;
	case CAM_UNCOR_PARITY:
		new_status = DID_PARITY;
		do_fallback = 1;
		break;
	case CAM_CMD_TIMEOUT:
		new_status = DID_TIME_OUT;
		do_fallback = 1;
		break;
	case CAM_REQ_CMP_ERR:
	case CAM_UNEXP_BUSFREE:
	case CAM_DATA_RUN_ERR:
		new_status = DID_ERROR;
		do_fallback = 1;
		break;
	case CAM_UA_ABORT:
	case CAM_NO_HBA:
	case CAM_SEQUENCE_FAIL:
	case CAM_CCB_LEN_ERR:
	case CAM_PROVIDE_FAIL:
	case CAM_REQ_TERMIO:
	case CAM_UNREC_HBA_ERROR:
	case CAM_REQ_TOO_BIG:
		new_status = DID_ERROR;
		break;
	case CAM_REQUEUE_REQ:
		new_status = DID_REQUEUE;
		break;
	default:
		/* We should never get here */
		new_status = DID_ERROR;
		break;
	}

	if (do_fallback) {
		printf("%s: device overrun (status %x) on %d:%d:%d\n",
		       ahd_name(ahd), status, cmd->device->channel,
		       cmd->device->id, cmd->device->lun);
	}

	ahd_cmd_set_transaction_status(cmd, new_status);

	cmd->scsi_done(cmd);
}