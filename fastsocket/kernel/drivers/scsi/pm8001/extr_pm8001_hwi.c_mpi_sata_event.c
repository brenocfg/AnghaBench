#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t u32 ;
struct task_status_struct {void* stat; void* resp; int /*<<< orphan*/  open_rej_reason; int /*<<< orphan*/  residual; } ;
struct sata_event_resp {int /*<<< orphan*/  device_id; int /*<<< orphan*/  port_id; int /*<<< orphan*/  tag; int /*<<< orphan*/  event; } ;
struct sas_task {int task_state_flags; int /*<<< orphan*/  (* task_done ) (struct sas_task*) ;int /*<<< orphan*/  task_state_lock; scalar_t__ uldd_task; struct task_status_struct task_status; int /*<<< orphan*/  dev; int /*<<< orphan*/  lldd_task; } ;
struct pm8001_hba_info {int /*<<< orphan*/  lock; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {int /*<<< orphan*/  running_req; } ;
struct pm8001_ccb_info {struct pm8001_device* device; struct sas_task* task; } ;

/* Variables and functions */
#define  IO_OPEN_CNX_ERROR_BAD_DESTINATION 148 
#define  IO_OPEN_CNX_ERROR_BREAK 147 
#define  IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED 146 
#define  IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS 145 
#define  IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED 144 
#define  IO_OPEN_CNX_ERROR_WRONG_DESTINATION 143 
#define  IO_OPEN_CNX_ERROR_ZONE_VIOLATION 142 
#define  IO_OVERFLOW 141 
#define  IO_XFER_CMD_FRAME_ISSUED 140 
 size_t IO_XFER_ERROR_ABORTED_NCQ_MODE ; 
#define  IO_XFER_ERROR_BREAK 139 
#define  IO_XFER_ERROR_NAK_RECEIVED 138 
#define  IO_XFER_ERROR_OFFSET_MISMATCH 137 
#define  IO_XFER_ERROR_PEER_ABORTED 136 
#define  IO_XFER_ERROR_PHY_NOT_READY 135 
#define  IO_XFER_ERROR_REJECTED_NCQ_MODE 134 
#define  IO_XFER_ERROR_UNEXPECTED_PHASE 133 
#define  IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED 132 
#define  IO_XFER_ERROR_XFER_RDY_OVERRUN 131 
#define  IO_XFER_ERROR_XFER_ZERO_DATA_LEN 130 
#define  IO_XFER_OPEN_RETRY_TIMEOUT 129 
#define  IO_XFER_PIO_SETUP_ERROR 128 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_IO_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 void* SAS_DATA_OVERRUN ; 
 void* SAS_DATA_UNDERRUN ; 
 void* SAS_DEV_NO_RESPONSE ; 
 void* SAS_INTERRUPTED ; 
 void* SAS_NAK_R_ERR ; 
 void* SAS_OPEN_REJECT ; 
 void* SAS_OPEN_TO ; 
 int /*<<< orphan*/  SAS_OREJ_BAD_DEST ; 
 int /*<<< orphan*/  SAS_OREJ_CONN_RATE ; 
 int /*<<< orphan*/  SAS_OREJ_EPROTO ; 
 int /*<<< orphan*/  SAS_OREJ_RSVD_CONT0 ; 
 int /*<<< orphan*/  SAS_OREJ_RSVD_RETRY ; 
 int /*<<< orphan*/  SAS_OREJ_UNKNOWN ; 
 int /*<<< orphan*/  SAS_OREJ_WRONG_DEST ; 
 void* SAS_QUEUE_FULL ; 
 int SAS_TASK_AT_INITIATOR ; 
 void* SAS_TASK_COMPLETE ; 
 int SAS_TASK_STATE_ABORTED ; 
 int SAS_TASK_STATE_DONE ; 
 int SAS_TASK_STATE_PENDING ; 
 void* SAS_TASK_UNDELIVERED ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pm8001_ccb_task_free (struct pm8001_hba_info*,struct sas_task*,struct pm8001_ccb_info*,size_t) ; 
 struct pm8001_device* pm8001_find_dev (struct pm8001_hba_info*,size_t) ; 
 int /*<<< orphan*/  pm8001_handle_event (struct pm8001_hba_info*,struct pm8001_device*,int const) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  pm8001_send_read_log (struct pm8001_hba_info*,struct pm8001_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sas_task*) ; 
 int /*<<< orphan*/  stub2 (struct sas_task*) ; 
 int /*<<< orphan*/  stub3 (struct sas_task*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mpi_sata_event(struct pm8001_hba_info *pm8001_ha , void *piomb)
{
	struct sas_task *t;
	struct task_status_struct *ts;
	struct pm8001_ccb_info *ccb;
	struct pm8001_device *pm8001_dev;
	struct sata_event_resp *psataPayload =
		(struct sata_event_resp *)(piomb + 4);
	u32 event = le32_to_cpu(psataPayload->event);
	u32 tag = le32_to_cpu(psataPayload->tag);
	u32 port_id = le32_to_cpu(psataPayload->port_id);
	u32 dev_id = le32_to_cpu(psataPayload->device_id);
	unsigned long flags;

	ccb = &pm8001_ha->ccb_info[tag];

	if (ccb) {
		t = ccb->task;
		pm8001_dev = ccb->device;
	} else {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("No CCB !!!. returning\n"));
	}
	if (event)
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("SATA EVENT 0x%x\n", event));

	/* Check if this is NCQ error */
	if (event == IO_XFER_ERROR_ABORTED_NCQ_MODE) {
		/* find device using device id */
		pm8001_dev = pm8001_find_dev(pm8001_ha, dev_id);
		/* send read log extension */
		if (pm8001_dev)
			pm8001_send_read_log(pm8001_ha, pm8001_dev);
		return;
	}

	ccb = &pm8001_ha->ccb_info[tag];
	t = ccb->task;
	pm8001_dev = ccb->device;
	if (event)
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("sata IO status 0x%x\n", event));
	if (unlikely(!t || !t->lldd_task || !t->dev))
		return;
	ts = &t->task_status;
	PM8001_IO_DBG(pm8001_ha, pm8001_printk(
		"port_id:0x%x, device_id:0x%x, tag:0x%x, event:0x%x\n",
		port_id, dev_id, tag, event));
	switch (event) {
	case IO_OVERFLOW:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk("IO_UNDERFLOW\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_OVERRUN;
		ts->residual = 0;
		if (pm8001_dev)
			pm8001_dev->running_req--;
		break;
	case IO_XFER_ERROR_BREAK:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_BREAK\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_INTERRUPTED;
		break;
	case IO_XFER_ERROR_PHY_NOT_READY:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_PHY_NOT_READY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
		break;
	case IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_PROTOCOL_NOT"
			"_SUPPORTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_EPROTO;
		break;
	case IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_UNKNOWN;
		break;
	case IO_OPEN_CNX_ERROR_BREAK:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_BREAK\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_CONT0;
		break;
	case IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n"));
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		if (!t->uldd_task) {
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
			mb();/*ditto*/
			spin_unlock_irq(&pm8001_ha->lock);
			t->task_done(t);
			spin_lock_irq(&pm8001_ha->lock);
			return;
		}
		break;
	case IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_BAD_DESTINATION\n"));
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_BAD_DEST;
		break;
	case IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_CONNECTION_RATE_"
			"NOT_SUPPORTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_CONN_RATE;
		break;
	case IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		PM8001_IO_DBG(pm8001_ha,
		       pm8001_printk("IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_WRONG_DEST;
		break;
	case IO_XFER_ERROR_NAK_RECEIVED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_NAK_RECEIVED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		break;
	case IO_XFER_ERROR_PEER_ABORTED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_PEER_ABORTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		break;
	case IO_XFER_ERROR_REJECTED_NCQ_MODE:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_REJECTED_NCQ_MODE\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		break;
	case IO_XFER_OPEN_RETRY_TIMEOUT:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_OPEN_RETRY_TIMEOUT\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	case IO_XFER_ERROR_UNEXPECTED_PHASE:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_UNEXPECTED_PHASE\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	case IO_XFER_ERROR_XFER_RDY_OVERRUN:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_XFER_RDY_OVERRUN\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	case IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED:
		PM8001_IO_DBG(pm8001_ha,
		       pm8001_printk("IO_XFER_ERROR_XFER_RDY_NOT_EXPECTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	case IO_XFER_ERROR_OFFSET_MISMATCH:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_OFFSET_MISMATCH\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	case IO_XFER_ERROR_XFER_ZERO_DATA_LEN:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_XFER_ZERO_DATA_LEN\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	case IO_XFER_CMD_FRAME_ISSUED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_CMD_FRAME_ISSUED\n"));
		break;
	case IO_XFER_PIO_SETUP_ERROR:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_PIO_SETUP_ERROR\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	default:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("Unknown status 0x%x\n", event));
		/* not allowed case. Therefore, return failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	}
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	if (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("task 0x%p done with io_status 0x%x"
			" resp 0x%x stat 0x%x but aborted by upper layer!\n",
			t, event, ts->resp, ts->stat));
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
	} else if (t->uldd_task) {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
		mb();/* ditto */
		spin_unlock_irq(&pm8001_ha->lock);
		t->task_done(t);
		spin_lock_irq(&pm8001_ha->lock);
	} else if (!t->uldd_task) {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
		mb();/*ditto*/
		spin_unlock_irq(&pm8001_ha->lock);
		t->task_done(t);
		spin_lock_irq(&pm8001_ha->lock);
	}
}