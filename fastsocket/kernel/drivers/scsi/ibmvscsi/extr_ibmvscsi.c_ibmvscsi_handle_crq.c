#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct viosrp_crq {int valid; int format; scalar_t__ status; scalar_t__ IU_data_ptr; } ;
struct srp_event_struct {TYPE_6__* hostdata; int /*<<< orphan*/  list; int /*<<< orphan*/  (* done ) (struct srp_event_struct*) ;TYPE_4__* cmnd; int /*<<< orphan*/  timer; TYPE_3__* xfer_iu; int /*<<< orphan*/  free; } ;
struct ibmvscsi_host_data {int client_migrated; int reenable_crq; int /*<<< orphan*/  dev; int /*<<< orphan*/  request_limit; int /*<<< orphan*/  pool; int /*<<< orphan*/  work_wait_q; int /*<<< orphan*/  host; } ;
struct TYPE_14__ {long (* send_crq ) (struct ibmvscsi_host_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {TYPE_5__* host; int /*<<< orphan*/  pool; } ;
struct TYPE_12__ {int /*<<< orphan*/  host_lock; } ;
struct TYPE_11__ {int result; } ;
struct TYPE_8__ {int /*<<< orphan*/  req_lim_delta; } ;
struct TYPE_9__ {TYPE_1__ rsp; } ;
struct TYPE_10__ {TYPE_2__ srp; } ;

/* Variables and functions */
 int DID_ERROR ; 
 int /*<<< orphan*/  DID_REQUEUE ; 
 int /*<<< orphan*/  IBMVSCSI_CRQ_INIT_COMPLETE ; 
 scalar_t__ VIOSRP_OK ; 
 scalar_t__ VIOSRP_OK2 ; 
 scalar_t__ VIOSRP_SRP_FORMAT ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_event_struct (int /*<<< orphan*/ *,struct srp_event_struct*) ; 
 TYPE_7__* ibmvscsi_ops ; 
 int /*<<< orphan*/  ibmvscsi_reset_host (struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  init_adapter (struct ibmvscsi_host_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  purge_requests (struct ibmvscsi_host_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 long stub1 (struct ibmvscsi_host_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct srp_event_struct*) ; 
 int /*<<< orphan*/  valid_event_struct (int /*<<< orphan*/ *,struct srp_event_struct*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void ibmvscsi_handle_crq(struct viosrp_crq *crq,
			 struct ibmvscsi_host_data *hostdata)
{
	long rc;
	unsigned long flags;
	struct srp_event_struct *evt_struct =
	    (struct srp_event_struct *)crq->IU_data_ptr;
	switch (crq->valid) {
	case 0xC0:		/* initialization */
		switch (crq->format) {
		case 0x01:	/* Initialization message */
			dev_info(hostdata->dev, "partner initialized\n");
			/* Send back a response */
			if ((rc = ibmvscsi_ops->send_crq(hostdata,
							 IBMVSCSI_CRQ_INIT_COMPLETE, 0)) == 0) {
				/* Now login */
				init_adapter(hostdata);
			} else {
				dev_err(hostdata->dev, "Unable to send init rsp. rc=%ld\n", rc);
			}

			break;
		case 0x02:	/* Initialization response */
			dev_info(hostdata->dev, "partner initialization complete\n");

			/* Now login */
			init_adapter(hostdata);
			break;
		default:
			dev_err(hostdata->dev, "unknown crq message type: %d\n", crq->format);
		}
		return;
	case 0xFF:	/* Hypervisor telling us the connection is closed */
		scsi_block_requests(hostdata->host);
		atomic_set(&hostdata->request_limit, 0);
		if (crq->format == 0x06) {
			/* We need to re-setup the interpartition connection */
			dev_info(hostdata->dev, "Re-enabling adapter!\n");
			hostdata->client_migrated = 1;
			hostdata->reenable_crq = 1;
			purge_requests(hostdata, DID_REQUEUE);
			wake_up(&hostdata->work_wait_q);
		} else {
			dev_err(hostdata->dev, "Virtual adapter failed rc %d!\n",
				crq->format);
			ibmvscsi_reset_host(hostdata);
		}
		return;
	case 0x80:		/* real payload */
		break;
	default:
		dev_err(hostdata->dev, "got an invalid message type 0x%02x\n",
			crq->valid);
		return;
	}

	/* The only kind of payload CRQs we should get are responses to
	 * things we send. Make sure this response is to something we
	 * actually sent
	 */
	if (!valid_event_struct(&hostdata->pool, evt_struct)) {
		dev_err(hostdata->dev, "returned correlation_token 0x%p is invalid!\n",
		       (void *)crq->IU_data_ptr);
		return;
	}

	if (atomic_read(&evt_struct->free)) {
		dev_err(hostdata->dev, "received duplicate correlation_token 0x%p!\n",
			(void *)crq->IU_data_ptr);
		return;
	}

	if (crq->format == VIOSRP_SRP_FORMAT)
		atomic_add(evt_struct->xfer_iu->srp.rsp.req_lim_delta,
			   &hostdata->request_limit);

	del_timer(&evt_struct->timer);

	if ((crq->status != VIOSRP_OK && crq->status != VIOSRP_OK2) && evt_struct->cmnd)
		evt_struct->cmnd->result = DID_ERROR << 16;
	if (evt_struct->done)
		evt_struct->done(evt_struct);
	else
		dev_err(hostdata->dev, "returned done() is NULL; not running it!\n");

	/*
	 * Lock the host_lock before messing with these structures, since we
	 * are running in a task context
	 */
	spin_lock_irqsave(evt_struct->hostdata->host->host_lock, flags);
	list_del(&evt_struct->list);
	free_event_struct(&evt_struct->hostdata->pool, evt_struct);
	spin_unlock_irqrestore(evt_struct->hostdata->host->host_lock, flags);
}