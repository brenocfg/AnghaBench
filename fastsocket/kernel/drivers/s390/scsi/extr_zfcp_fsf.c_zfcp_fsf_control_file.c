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
typedef  int /*<<< orphan*/  u8 ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  completion; int /*<<< orphan*/  queue_req; TYPE_2__* qtcb; int /*<<< orphan*/  handler; } ;
struct zfcp_fsf_cfdc {int /*<<< orphan*/  sg; int /*<<< orphan*/  option; int /*<<< orphan*/  command; } ;
struct zfcp_adapter {int adapter_features; struct zfcp_qdio* qdio; } ;
struct qdio_buffer_element {int /*<<< orphan*/  sflags; } ;
struct fsf_qtcb_bottom_support {int /*<<< orphan*/  option; int /*<<< orphan*/  operation_subtype; } ;
struct TYPE_3__ {struct fsf_qtcb_bottom_support support; } ;
struct TYPE_4__ {TYPE_1__ bottom; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 struct zfcp_fsf_req* ERR_PTR (int) ; 
 int /*<<< orphan*/  FSF_CFDC_OPERATION_SUBTYPE ; 
 int FSF_FEATURE_CFDC ; 
 int /*<<< orphan*/  FSF_MAX_SBALS_PER_REQ ; 
#define  FSF_QTCB_DOWNLOAD_CONTROL_FILE 129 
#define  FSF_QTCB_UPLOAD_CONTROL_FILE 128 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_READ ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_TYPE_WRITE ; 
 scalar_t__ ZFCP_CFDC_MAX_SIZE ; 
 int /*<<< orphan*/  ZFCP_FSF_REQUEST_TIMEOUT ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ zfcp_adapter_multi_buffer_active (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_fsf_control_file_handler ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 scalar_t__ zfcp_fsf_req_sbal_get (struct zfcp_qdio*) ; 
 int zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_start_timer (struct zfcp_fsf_req*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfcp_qdio_real_bytes (int /*<<< orphan*/ ) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_req (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 
 int zfcp_qdio_sbals_from_sg (struct zfcp_qdio*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_qdio_set_sbale_last (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_set_scount (struct zfcp_qdio*,int /*<<< orphan*/ *) ; 

struct zfcp_fsf_req *zfcp_fsf_control_file(struct zfcp_adapter *adapter,
					   struct zfcp_fsf_cfdc *fsf_cfdc)
{
	struct qdio_buffer_element *sbale;
	struct zfcp_qdio *qdio = adapter->qdio;
	struct zfcp_fsf_req *req = NULL;
	struct fsf_qtcb_bottom_support *bottom;
	int retval = -EIO;
	u8 direction;

	if (!(adapter->adapter_features & FSF_FEATURE_CFDC))
		return ERR_PTR(-EOPNOTSUPP);

	switch (fsf_cfdc->command) {
	case FSF_QTCB_DOWNLOAD_CONTROL_FILE:
		direction = SBAL_SFLAGS0_TYPE_WRITE;
		break;
	case FSF_QTCB_UPLOAD_CONTROL_FILE:
		direction = SBAL_SFLAGS0_TYPE_READ;
		break;
	default:
		return ERR_PTR(-EINVAL);
	}

	spin_lock_bh(&qdio->req_q_lock);
	if (zfcp_fsf_req_sbal_get(qdio))
		goto out;

	req = zfcp_fsf_req_create(qdio, fsf_cfdc->command, NULL);
	if (IS_ERR(req)) {
		retval = -EPERM;
		goto out;
	}

	req->handler = zfcp_fsf_control_file_handler;

	sbale = zfcp_qdio_sbale_req(qdio, &req->queue_req);
	sbale[0].sflags |= direction;

	bottom = &req->qtcb->bottom.support;
	bottom->operation_subtype = FSF_CFDC_OPERATION_SUBTYPE;
	bottom->option = fsf_cfdc->option;

	retval = zfcp_qdio_sbals_from_sg(qdio, &req->queue_req,
					 direction, fsf_cfdc->sg,
					 FSF_MAX_SBALS_PER_REQ);
	if (retval ||
	    (zfcp_qdio_real_bytes(fsf_cfdc->sg) != ZFCP_CFDC_MAX_SIZE)) {
		zfcp_fsf_req_free(req);
		retval = -EIO;
		goto out;
	}
	zfcp_qdio_set_sbale_last(qdio, &req->queue_req);
	if (zfcp_adapter_multi_buffer_active(adapter))
		zfcp_qdio_set_scount(qdio, &req->queue_req);

	zfcp_fsf_start_timer(req, ZFCP_FSF_REQUEST_TIMEOUT);
	retval = zfcp_fsf_req_send(req);
out:
	spin_unlock_bh(&qdio->req_q_lock);

	if (!retval) {
		wait_for_completion(&req->completion);
		return req;
	}
	return ERR_PTR(retval);
}