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
struct TYPE_6__ {int /*<<< orphan*/  count; struct qdio_buffer** sbal; } ;
struct zfcp_qdio {TYPE_3__ resp_q; struct zfcp_adapter* adapter; } ;
struct TYPE_5__ {int sbal_response; int /*<<< orphan*/  qdio_inb_usage; } ;
struct zfcp_fsf_req {TYPE_2__ queue_req; int /*<<< orphan*/  list; } ;
struct zfcp_adapter {int /*<<< orphan*/  req_list_lock; TYPE_1__* ccw_device; } ;
struct qdio_buffer_element {int eflags; scalar_t__ addr; } ;
struct qdio_buffer {struct qdio_buffer_element* element; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int QDIO_MAX_ELEMENTS_PER_BUFFER ; 
 int SBAL_EFLAGS_LAST_ENTRY ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_fsf_req_complete (struct zfcp_fsf_req*) ; 
 int /*<<< orphan*/  zfcp_qdio_siosl (struct zfcp_adapter*) ; 
 struct zfcp_fsf_req* zfcp_reqlist_find (struct zfcp_adapter*,unsigned long) ; 

void zfcp_fsf_reqid_check(struct zfcp_qdio *qdio, int sbal_idx)
{
	struct zfcp_adapter *adapter = qdio->adapter;
	struct qdio_buffer *sbal = qdio->resp_q.sbal[sbal_idx];
	struct qdio_buffer_element *sbale;
	struct zfcp_fsf_req *fsf_req;
	unsigned long flags, req_id;
	int idx;

	for (idx = 0; idx < QDIO_MAX_ELEMENTS_PER_BUFFER; idx++) {

		sbale = &sbal->element[idx];
		req_id = (unsigned long) sbale->addr;
		spin_lock_irqsave(&adapter->req_list_lock, flags);
		fsf_req = zfcp_reqlist_find(adapter, req_id);

		if (!fsf_req) {
			/*
			 * Unknown request means that we have potentially memory
			 * corruption and must stop the machine immediately.
			 */
			zfcp_qdio_siosl(adapter);
			panic("error: unknown req_id (%lx) on adapter %s.\n",
			      req_id, dev_name(&adapter->ccw_device->dev));
		}

		list_del(&fsf_req->list);
		spin_unlock_irqrestore(&adapter->req_list_lock, flags);

		fsf_req->queue_req.sbal_response = sbal_idx;
		fsf_req->queue_req.qdio_inb_usage =
			atomic_read(&qdio->resp_q.count);
		zfcp_fsf_req_complete(fsf_req);

		if (likely(sbale->eflags & SBAL_EFLAGS_LAST_ENTRY))
			break;
	}
}