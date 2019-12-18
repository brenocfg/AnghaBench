#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zfcp_qdio {int /*<<< orphan*/  req_q_lock; struct zfcp_adapter* adapter; } ;
struct TYPE_5__ {int sbale_curr; } ;
struct zfcp_fsf_req {TYPE_2__ queue_req; struct fsf_status_read_buffer* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  status_read_data; int /*<<< orphan*/  status_read_req; } ;
struct zfcp_adapter {int /*<<< orphan*/  dbf; TYPE_1__ pool; } ;
struct qdio_buffer_element {int length; void* addr; int /*<<< orphan*/  eflags; } ;
struct fsf_status_read_buffer {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FSF_QTCB_UNSOLICITED_STATUS ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IS_ERR (struct zfcp_fsf_req*) ; 
 int PTR_ERR (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  SBAL_EFLAGS_LAST_ENTRY ; 
 struct fsf_status_read_buffer* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct fsf_status_read_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fsf_status_read_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_fsf_unsol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct zfcp_fsf_req* zfcp_fsf_req_create (struct zfcp_qdio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 scalar_t__ zfcp_fsf_req_sbal_get (struct zfcp_qdio*) ; 
 int zfcp_fsf_req_send (struct zfcp_fsf_req*) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_curr (struct zfcp_qdio*,TYPE_2__*) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_req (struct zfcp_qdio*,TYPE_2__*) ; 

int zfcp_fsf_status_read(struct zfcp_qdio *qdio)
{
	struct zfcp_adapter *adapter = qdio->adapter;
	struct zfcp_fsf_req *req;
	struct fsf_status_read_buffer *sr_buf;
	struct qdio_buffer_element *sbale;
	int retval = -EIO;

	spin_lock_bh(&qdio->req_q_lock);
	if (zfcp_fsf_req_sbal_get(qdio))
		goto out;

	req = zfcp_fsf_req_create(qdio, FSF_QTCB_UNSOLICITED_STATUS,
				  adapter->pool.status_read_req);
	if (IS_ERR(req)) {
		retval = PTR_ERR(req);
		goto out;
	}

	sbale = zfcp_qdio_sbale_req(qdio, &req->queue_req);
	sbale[2].eflags |= SBAL_EFLAGS_LAST_ENTRY;
	req->queue_req.sbale_curr = 2;

	sr_buf = mempool_alloc(adapter->pool.status_read_data, GFP_ATOMIC);
	if (!sr_buf) {
		retval = -ENOMEM;
		goto failed_buf;
	}
	memset(sr_buf, 0, sizeof(*sr_buf));
	req->data = sr_buf;
	sbale = zfcp_qdio_sbale_curr(qdio, &req->queue_req);
	sbale->addr = (void *) sr_buf;
	sbale->length = sizeof(*sr_buf);

	retval = zfcp_fsf_req_send(req);
	if (retval)
		goto failed_req_send;

	goto out;

failed_req_send:
	mempool_free(sr_buf, adapter->pool.status_read_data);
failed_buf:
	zfcp_fsf_req_free(req);
	zfcp_dbf_hba_fsf_unsol("fail", adapter->dbf, NULL);
out:
	spin_unlock_bh(&qdio->req_q_lock);
	return retval;
}