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
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; } ;
struct zfcp_fsf_req {TYPE_7__* qtcb; struct zfcp_erp_action* erp_action; TYPE_4__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  queue_req; int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {struct zfcp_fsf_req* fsf_req; TYPE_4__* unit; TYPE_3__* port; struct zfcp_adapter* adapter; } ;
struct TYPE_8__ {int /*<<< orphan*/  erp_req; } ;
struct zfcp_adapter {int connection_features; TYPE_1__ pool; struct zfcp_qdio* qdio; } ;
struct qdio_buffer_element {int /*<<< orphan*/  eflags; int /*<<< orphan*/  sflags; } ;
struct TYPE_12__ {int /*<<< orphan*/  option; int /*<<< orphan*/  fcp_lun; } ;
struct TYPE_13__ {TYPE_5__ support; } ;
struct TYPE_9__ {int /*<<< orphan*/  port_handle; } ;
struct TYPE_14__ {TYPE_6__ bottom; TYPE_2__ header; } ;
struct TYPE_11__ {int /*<<< orphan*/  fcp_lun; } ;
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EIO ; 
 int FSF_FEATURE_NPIV_MODE ; 
 int /*<<< orphan*/  FSF_OPEN_LUN_SUPPRESS_BOXING ; 
 int /*<<< orphan*/  FSF_QTCB_OPEN_LUN ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int PTR_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_EFLAGS_LAST_ENTRY ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_READ ; 
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_CLEANUP ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_open_unit_handler ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 scalar_t__ zfcp_fsf_req_sbal_get (struct zfcp_qdio*) ; 
 int zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_start_erp_timer (struct zfcp_fsf_req*) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_req (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 

int zfcp_fsf_open_unit(struct zfcp_erp_action *erp_action)
{
	struct qdio_buffer_element *sbale;
	struct zfcp_adapter *adapter = erp_action->adapter;
	struct zfcp_qdio *qdio = adapter->qdio;
	struct zfcp_fsf_req *req;
	int retval = -EIO;

	spin_lock_bh(&qdio->req_q_lock);
	if (zfcp_fsf_req_sbal_get(qdio))
		goto out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_OPEN_LUN,
				  adapter->pool.erp_req);

	if (IS_ERR(req)) {
		retval = PTR_ERR(req);
		goto out;
	}

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;
	sbale = zfcp_qdio_sbale_req(qdio, &req->queue_req);
	sbale[0].sflags |= SBAL_SFLAGS0_TYPE_READ;
	sbale[1].eflags |= SBAL_EFLAGS_LAST_ENTRY;

	req->qtcb->header.port_handle = erp_action->port->handle;
	req->qtcb->bottom.support.fcp_lun = erp_action->unit->fcp_lun;
	req->handler = zfcp_fsf_open_unit_handler;
	req->data = erp_action->unit;
	req->erp_action = erp_action;
	erp_action->fsf_req = req;

	if (!(adapter->connection_features & FSF_FEATURE_NPIV_MODE))
		req->qtcb->bottom.support.option = FSF_OPEN_LUN_SUPPRESS_BOXING;

	zfcp_fsf_start_erp_timer(req);
	retval = zfcp_fsf_req_send(req);
	if (retval) {
		zfcp_fsf_req_free(req);
		erp_action->fsf_req = NULL;
	}
out:
	spin_unlock_bh(&qdio->req_q_lock);
	return retval;
}