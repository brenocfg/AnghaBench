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
typedef  int /*<<< orphan*/  u8 ;
struct zfcp_unit {TYPE_4__* port; int /*<<< orphan*/  handle; int /*<<< orphan*/  status; } ;
struct TYPE_8__ {int /*<<< orphan*/  count; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; int /*<<< orphan*/  req_q_full; TYPE_1__ req_q; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  queue_req; TYPE_7__* qtcb; int /*<<< orphan*/  handler; struct scsi_cmnd* data; struct zfcp_unit* unit; int /*<<< orphan*/  status; scalar_t__ req_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  scsi_req; } ;
struct zfcp_adapter {struct zfcp_qdio* qdio; TYPE_2__ pool; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; unsigned char* host_scribble; TYPE_5__* device; } ;
struct fsf_qtcb_bottom_io {int ref_tag_value; int /*<<< orphan*/  prot_data_length; int /*<<< orphan*/  fcp_cmnd; int /*<<< orphan*/  data_direction; int /*<<< orphan*/  data_block_length; int /*<<< orphan*/  fcp_cmnd_length; int /*<<< orphan*/  service_class; } ;
struct fcp_cmnd {int dummy; } ;
struct TYPE_13__ {struct fsf_qtcb_bottom_io io; } ;
struct TYPE_10__ {int /*<<< orphan*/  port_handle; int /*<<< orphan*/  lun_handle; } ;
struct TYPE_14__ {TYPE_6__ bottom; TYPE_3__ header; } ;
struct TYPE_12__ {int /*<<< orphan*/  sector_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  handle; struct zfcp_adapter* adapter; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  FCP_CMND_LEN ; 
 int /*<<< orphan*/  FSF_CLASS_3 ; 
 int /*<<< orphan*/  FSF_MAX_SBALS_PER_REQ ; 
 int /*<<< orphan*/  FSF_QTCB_FCP_CMND ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int PTR_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_READ ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_WRITE ; 
 scalar_t__ SCSI_PROT_NORMAL ; 
 int ZFCP_STATUS_COMMON_UNBLOCKED ; 
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_CLEANUP ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int scsi_get_lba (struct scsi_cmnd*) ; 
 scalar_t__ scsi_get_prot_op (struct scsi_cmnd*) ; 
 scalar_t__ scsi_prot_sg_count (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_prot_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ zfcp_adapter_multi_buffer_active (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fc_scsi_to_fcp (struct fcp_cmnd*,struct scsi_cmnd*) ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 int zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_send_fcp_command_handler ; 
 scalar_t__ zfcp_fsf_set_data_dir (struct scsi_cmnd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_real_bytes (int /*<<< orphan*/ ) ; 
 int zfcp_qdio_sbals_from_sg (struct zfcp_qdio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_qdio_set_data_div (struct zfcp_qdio*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zfcp_qdio_set_sbale_last (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_set_scount (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_unit_get (struct zfcp_unit*) ; 
 int /*<<< orphan*/  zfcp_unit_put (struct zfcp_unit*) ; 

int zfcp_fsf_send_fcp_command_task(struct zfcp_unit *unit,
				   struct scsi_cmnd *scsi_cmnd)
{
	struct zfcp_fsf_req *req;
	struct fcp_cmnd *fcp_cmnd;
	u8 sbtype = SBAL_SFLAGS0_TYPE_READ;
	int retval = -EIO;
	struct zfcp_adapter *adapter = unit->port->adapter;
	struct zfcp_qdio *qdio = adapter->qdio;
	struct fsf_qtcb_bottom_io *io;

	if (unlikely(!(atomic_read(&unit->status) &
		       ZFCP_STATUS_COMMON_UNBLOCKED)))
		return -EBUSY;

	spin_lock(&qdio->req_q_lock);
	if (atomic_read(&qdio->req_q.count) <= 0) {
		atomic_inc(&qdio->req_q_full);
		goto out;
	}

	if (scsi_cmnd->sc_data_direction == DMA_TO_DEVICE)
		sbtype = SBAL_SFLAGS0_TYPE_WRITE;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_FCP_CMND,
				  adapter->pool.scsi_req);

	if (IS_ERR(req)) {
		retval = PTR_ERR(req);
		goto out;
	}

	scsi_cmnd->host_scribble = (unsigned char *) req->req_id;

	io = &req->qtcb->bottom.io;
	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	zfcp_unit_get(unit);
	req->unit = unit;
	req->data = scsi_cmnd;
	req->handler = zfcp_fsf_send_fcp_command_handler;
	req->qtcb->header.lun_handle = unit->handle;
	req->qtcb->header.port_handle = unit->port->handle;
	io->service_class = FSF_CLASS_3;
	io->fcp_cmnd_length = FCP_CMND_LEN;

	if (scsi_get_prot_op(scsi_cmnd) != SCSI_PROT_NORMAL) {
		io->data_block_length = scsi_cmnd->device->sector_size;
		io->ref_tag_value = scsi_get_lba(scsi_cmnd) & 0xFFFFFFFF;
	}

	if (zfcp_fsf_set_data_dir(scsi_cmnd, &io->data_direction))
		goto failed_scsi_cmnd;

	fcp_cmnd = (struct fcp_cmnd *) &req->qtcb->bottom.io.fcp_cmnd;
	zfcp_fc_scsi_to_fcp(fcp_cmnd, scsi_cmnd);

	if (scsi_prot_sg_count(scsi_cmnd)) {
		zfcp_qdio_set_data_div(qdio, &req->queue_req,
				       scsi_prot_sg_count(scsi_cmnd));
		retval = zfcp_qdio_sbals_from_sg(qdio, &req->queue_req,
						 sbtype,
						 scsi_prot_sglist(scsi_cmnd),
						 FSF_MAX_SBALS_PER_REQ);
		if (retval)
			goto failed_scsi_cmnd;
		io->prot_data_length = zfcp_qdio_real_bytes(
						scsi_prot_sglist(scsi_cmnd));
	}

	retval = zfcp_qdio_sbals_from_sg(qdio, &req->queue_req, sbtype,
					 scsi_sglist(scsi_cmnd),
					 FSF_MAX_SBALS_PER_REQ);
	if (unlikely(retval))
		goto failed_scsi_cmnd;

	zfcp_qdio_set_sbale_last(adapter->qdio, &req->queue_req);
	if (zfcp_adapter_multi_buffer_active(adapter))
		zfcp_qdio_set_scount(qdio, &req->queue_req);

	retval = zfcp_fsf_req_send(req);
	if (unlikely(retval))
		goto failed_scsi_cmnd;

	goto out;

failed_scsi_cmnd:
	zfcp_unit_put(unit);
	zfcp_fsf_req_free(req);
	scsi_cmnd->host_scribble = NULL;
out:
	spin_unlock(&qdio->req_q_lock);
	return retval;
}