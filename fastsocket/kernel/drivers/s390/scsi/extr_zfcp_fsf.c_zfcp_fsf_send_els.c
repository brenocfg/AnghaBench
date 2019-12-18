#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zfcp_send_els {int /*<<< orphan*/  d_id; int /*<<< orphan*/  resp; int /*<<< orphan*/  req; TYPE_4__* adapter; } ;
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; } ;
struct zfcp_fsf_req {struct zfcp_send_els* data; int /*<<< orphan*/  handler; TYPE_3__* qtcb; int /*<<< orphan*/  queue_req; int /*<<< orphan*/  status; } ;
struct TYPE_8__ {struct zfcp_qdio* qdio; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_id; } ;
struct TYPE_6__ {TYPE_1__ support; } ;
struct TYPE_7__ {TYPE_2__ bottom; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FSF_QTCB_SEND_ELS ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int PTR_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  ZFCP_STATUS_FSFREQ_CLEANUP ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_adapter_multi_buffer_active (TYPE_4__*) ; 
 int /*<<< orphan*/  zfcp_dbf_san_els_request (struct zfcp_fsf_req*) ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 scalar_t__ zfcp_fsf_req_sbal_get (struct zfcp_qdio*) ; 
 int zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_fsf_send_els_handler ; 
 int zfcp_fsf_setup_ct_els (struct zfcp_fsf_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  zfcp_qdio_sbal_limit (struct zfcp_qdio*,int /*<<< orphan*/ *,int) ; 

int zfcp_fsf_send_els(struct zfcp_send_els *els, unsigned int timeout)
{
	struct zfcp_fsf_req *req;
	struct zfcp_qdio *qdio = els->adapter->qdio;
	int ret = -EIO;

	spin_lock_bh(&qdio->req_q_lock);
	if (zfcp_fsf_req_sbal_get(qdio))
		goto out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_SEND_ELS, NULL);

	if (IS_ERR(req)) {
		ret = PTR_ERR(req);
		goto out;
	}

	req->status |= ZFCP_STATUS_FSFREQ_CLEANUP;

#if 1 /* FIXME */
	if (!zfcp_adapter_multi_buffer_active(els->adapter))
		zfcp_qdio_sbal_limit(qdio, &req->queue_req, 2);
#endif

	ret = zfcp_fsf_setup_ct_els(req, els->req, els->resp, 2, timeout);

	if (ret)
		goto failed_send;

	req->qtcb->bottom.support.d_id = els->d_id;
	req->handler = zfcp_fsf_send_els_handler;
	req->data = els;

	zfcp_dbf_san_els_request(req);

	ret = zfcp_fsf_req_send(req);
	if (ret)
		goto failed_send;

	goto out;

failed_send:
	zfcp_fsf_req_free(req);
out:
	spin_unlock_bh(&qdio->req_q_lock);
	return ret;
}