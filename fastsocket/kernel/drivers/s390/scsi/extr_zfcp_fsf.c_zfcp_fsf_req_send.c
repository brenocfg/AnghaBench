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
struct TYPE_3__ {int /*<<< orphan*/  count; } ;
struct zfcp_qdio {TYPE_1__ req_q; } ;
struct TYPE_4__ {int /*<<< orphan*/  qdio_outb_usage; } ;
struct zfcp_fsf_req {int /*<<< orphan*/  timer; TYPE_2__ queue_req; int /*<<< orphan*/  issued; int /*<<< orphan*/  list; int /*<<< orphan*/  req_id; int /*<<< orphan*/ * qtcb; struct zfcp_adapter* adapter; } ;
struct zfcp_adapter {int /*<<< orphan*/  req_no; int /*<<< orphan*/  fsf_req_seq_no; int /*<<< orphan*/  req_list_lock; int /*<<< orphan*/ * req_list; struct zfcp_qdio* qdio; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_clock () ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*,struct zfcp_fsf_req*) ; 
 scalar_t__ zfcp_qdio_send (struct zfcp_qdio*,TYPE_2__*) ; 
 scalar_t__ zfcp_reqlist_find_safe (struct zfcp_adapter*,struct zfcp_fsf_req*) ; 
 int zfcp_reqlist_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_reqlist_remove (struct zfcp_adapter*,struct zfcp_fsf_req*) ; 

__attribute__((used)) static int zfcp_fsf_req_send(struct zfcp_fsf_req *req)
{
	struct zfcp_adapter *adapter = req->adapter;
	struct zfcp_qdio *qdio = adapter->qdio;
	unsigned long	     flags;
	int		     idx;
	int		     with_qtcb = (req->qtcb != NULL);

	/* put allocated FSF request into hash table */
	spin_lock_irqsave(&adapter->req_list_lock, flags);
	idx = zfcp_reqlist_hash(req->req_id);
	list_add_tail(&req->list, &adapter->req_list[idx]);
	spin_unlock_irqrestore(&adapter->req_list_lock, flags);

	req->queue_req.qdio_outb_usage = atomic_read(&qdio->req_q.count);
	req->issued = get_clock();
	if (zfcp_qdio_send(qdio, &req->queue_req)) {
		del_timer(&req->timer);
		spin_lock_irqsave(&adapter->req_list_lock, flags);
		/* lookup request again, list might have changed */
		if (zfcp_reqlist_find_safe(adapter, req))
			zfcp_reqlist_remove(adapter, req);
		spin_unlock_irqrestore(&adapter->req_list_lock, flags);
		zfcp_erp_adapter_reopen(adapter, 0, "fsrs__1", req);
		return -EIO;
	}

	/* Don't increase for unsolicited status */
	if (with_qtcb)
		adapter->fsf_req_seq_no++;
	adapter->req_no++;

	return 0;
}