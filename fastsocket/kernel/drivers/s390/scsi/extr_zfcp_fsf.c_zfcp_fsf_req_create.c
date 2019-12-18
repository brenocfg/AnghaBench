#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct zfcp_qdio_queue {int /*<<< orphan*/  first; } ;
struct zfcp_qdio {struct zfcp_adapter* adapter; struct zfcp_qdio_queue req_q; } ;
struct TYPE_10__ {int sbal_number; int sbale_curr; int /*<<< orphan*/  sbal_last; int /*<<< orphan*/  sbal_first; } ;
struct zfcp_fsf_req {size_t fsf_command; scalar_t__ req_id; TYPE_4__* qtcb; int /*<<< orphan*/  seq_no; TYPE_5__ queue_req; struct zfcp_adapter* adapter; int /*<<< orphan*/  completion; int /*<<< orphan*/  timer; int /*<<< orphan*/  list; } ;
struct TYPE_6__ {int /*<<< orphan*/ * qtcb_pool; } ;
struct zfcp_adapter {scalar_t__ req_no; int /*<<< orphan*/  fsf_req_seq_no; TYPE_1__ pool; } ;
struct qdio_buffer_element {int length; void* addr; int /*<<< orphan*/  sflags; scalar_t__ eflags; } ;
struct fsf_qtcb {int dummy; } ;
typedef  int /*<<< orphan*/  mempool_t ;
struct TYPE_8__ {scalar_t__ req_id; int ulp_info; int /*<<< orphan*/  req_seq_no; int /*<<< orphan*/  qtcb_version; int /*<<< orphan*/  qtcb_type; } ;
struct TYPE_7__ {scalar_t__ req_handle; size_t fsf_command; } ;
struct TYPE_9__ {TYPE_3__ prefix; TYPE_2__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct zfcp_fsf_req* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FSF_QTCB_CURRENT_VERSION ; 
 scalar_t__ FSF_QTCB_UNSOLICITED_STATUS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SBAL_SFLAGS0_COMMAND ; 
 int /*<<< orphan*/ * fsf_qtcb_type ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 
 struct zfcp_fsf_req* zfcp_fsf_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_fsf_req_free (struct zfcp_fsf_req*) ; 
 struct qdio_buffer_element* zfcp_qdio_sbale_req (struct zfcp_qdio*,TYPE_5__*) ; 
 void* zfcp_qtcb_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct zfcp_fsf_req *zfcp_fsf_req_create(struct zfcp_qdio *qdio,
						u32 fsf_cmd, mempool_t *pool)
{
	struct qdio_buffer_element *sbale;
	struct zfcp_qdio_queue *req_q = &qdio->req_q;
	struct zfcp_adapter *adapter = qdio->adapter;
	struct zfcp_fsf_req *req = zfcp_fsf_alloc(pool);

	if (unlikely(!req))
		return ERR_PTR(-ENOMEM);

	if (adapter->req_no == 0)
		adapter->req_no++;

	INIT_LIST_HEAD(&req->list);
	init_timer(&req->timer);
	init_completion(&req->completion);

	req->adapter = adapter;
	req->fsf_command = fsf_cmd;
	req->req_id = adapter->req_no;
	req->queue_req.sbal_number = 1;
	req->queue_req.sbal_first = req_q->first;
	req->queue_req.sbal_last = req_q->first;
	req->queue_req.sbale_curr = 1;

	sbale = zfcp_qdio_sbale_req(qdio, &req->queue_req);
	sbale[0].addr = (void *) req->req_id;
	sbale[0].eflags = 0;
	sbale[0].sflags |= SBAL_SFLAGS0_COMMAND;

	if (likely(fsf_cmd != FSF_QTCB_UNSOLICITED_STATUS)) {
		if (likely(pool))
			req->qtcb = zfcp_qtcb_alloc(adapter->pool.qtcb_pool);
		else
			req->qtcb = zfcp_qtcb_alloc(NULL);

		if (unlikely(!req->qtcb)) {
			zfcp_fsf_req_free(req);
			return ERR_PTR(-ENOMEM);
		}

		req->qtcb->prefix.req_seq_no = adapter->fsf_req_seq_no;
		req->qtcb->prefix.req_id = req->req_id;
		req->qtcb->prefix.ulp_info = 26;
		req->qtcb->prefix.qtcb_type = fsf_qtcb_type[req->fsf_command];
		req->qtcb->prefix.qtcb_version = FSF_QTCB_CURRENT_VERSION;
		req->qtcb->header.req_handle = req->req_id;
		req->qtcb->header.fsf_command = req->fsf_command;
		req->seq_no = adapter->fsf_req_seq_no;
		req->qtcb->prefix.req_seq_no = adapter->fsf_req_seq_no;
		sbale[1].addr = (void *) req->qtcb;
		sbale[1].length = sizeof(struct fsf_qtcb);
	}

	return req;
}