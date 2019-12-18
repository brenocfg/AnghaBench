#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct task_status_struct {scalar_t__ resp; int stat; int /*<<< orphan*/  buf_valid_size; int /*<<< orphan*/  buf; int /*<<< orphan*/  open_rej_reason; int /*<<< orphan*/  residual; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  sense_buffer; scalar_t__ underflow; } ;
struct sas_task {int /*<<< orphan*/  list; TYPE_3__* dev; struct task_status_struct task_status; } ;
struct TYPE_6__ {TYPE_2__* port; } ;
struct TYPE_5__ {TYPE_1__* ha; } ;
struct TYPE_4__ {int /*<<< orphan*/  sas_ha_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSIGN_SAS_TASK (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int DID_ABORT ; 
 int DID_BAD_TARGET ; 
 int DID_ERROR ; 
 int DID_NO_CONNECT ; 
 int DID_PARITY ; 
 int DID_SOFT_ERROR ; 
#define  SAM_STAT_CHECK_CONDITION 141 
#define  SAS_ABORTED_TASK 140 
#define  SAS_DATA_OVERRUN 139 
#define  SAS_DATA_UNDERRUN 138 
#define  SAS_DEVICE_UNKNOWN 137 
#define  SAS_DEV_NO_RESPONSE 136 
 int /*<<< orphan*/  SAS_DPRINTK (char*,int /*<<< orphan*/ ) ; 
#define  SAS_INTERRUPTED 135 
#define  SAS_NAK_R_ERR 134 
#define  SAS_OPEN_REJECT 133 
#define  SAS_OPEN_TO 132 
 int /*<<< orphan*/  SAS_OREJ_RSVD_RETRY ; 
#define  SAS_PHY_DOWN 131 
#define  SAS_PROTO_RESPONSE 130 
#define  SAS_QUEUE_FULL 129 
#define  SAS_SG_ERR 128 
 scalar_t__ SAS_TASK_UNDELIVERED ; 
 int /*<<< orphan*/  SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sas_free_task (struct sas_task*) ; 
 scalar_t__ scsi_bufflen (struct scsi_cmnd*) ; 
 scalar_t__ scsi_get_resid (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sas_end_task(struct scsi_cmnd *sc, struct sas_task *task)
{
	struct task_status_struct *ts = &task->task_status;
	int hs = 0, stat = 0;

	if (ts->resp == SAS_TASK_UNDELIVERED) {
		/* transport error */
		hs = DID_NO_CONNECT;
	} else { /* ts->resp == SAS_TASK_COMPLETE */
		/* task delivered, what happened afterwards? */
		switch (ts->stat) {
		case SAS_DEV_NO_RESPONSE:
		case SAS_INTERRUPTED:
		case SAS_PHY_DOWN:
		case SAS_NAK_R_ERR:
		case SAS_OPEN_TO:
			hs = DID_NO_CONNECT;
			break;
		case SAS_DATA_UNDERRUN:
			scsi_set_resid(sc, ts->residual);
			if (scsi_bufflen(sc) - scsi_get_resid(sc) < sc->underflow)
				hs = DID_ERROR;
			break;
		case SAS_DATA_OVERRUN:
			hs = DID_ERROR;
			break;
		case SAS_QUEUE_FULL:
			hs = DID_SOFT_ERROR; /* retry */
			break;
		case SAS_DEVICE_UNKNOWN:
			hs = DID_BAD_TARGET;
			break;
		case SAS_SG_ERR:
			hs = DID_PARITY;
			break;
		case SAS_OPEN_REJECT:
			if (ts->open_rej_reason == SAS_OREJ_RSVD_RETRY)
				hs = DID_SOFT_ERROR; /* retry */
			else
				hs = DID_ERROR;
			break;
		case SAS_PROTO_RESPONSE:
			SAS_DPRINTK("LLDD:%s sent SAS_PROTO_RESP for an SSP "
				    "task; please report this\n",
				    task->dev->port->ha->sas_ha_name);
			break;
		case SAS_ABORTED_TASK:
			hs = DID_ABORT;
			break;
		case SAM_STAT_CHECK_CONDITION:
			memcpy(sc->sense_buffer, ts->buf,
			       min(SCSI_SENSE_BUFFERSIZE, ts->buf_valid_size));
			stat = SAM_STAT_CHECK_CONDITION;
			break;
		default:
			stat = ts->stat;
			break;
		}
	}

	sc->result = (hs << 16) | stat;
	ASSIGN_SAS_TASK(sc, NULL);
	list_del_init(&task->list);
	sas_free_task(task);
}