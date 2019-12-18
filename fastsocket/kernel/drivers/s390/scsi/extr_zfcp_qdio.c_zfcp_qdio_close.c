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
struct zfcp_qdio_queue {int first; int /*<<< orphan*/  count; int /*<<< orphan*/  sbal; } ;
struct TYPE_4__ {int /*<<< orphan*/  count; int /*<<< orphan*/  first; } ;
struct zfcp_qdio {TYPE_2__ resp_q; TYPE_1__* adapter; int /*<<< orphan*/  req_q_wq; int /*<<< orphan*/  req_q_lock; struct zfcp_qdio_queue req_q; } ;
struct TYPE_3__ {int /*<<< orphan*/  ccw_device; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  QDIO_FLAG_CLEANUP_USING_CLEAR ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int ZFCP_STATUS_ADAPTER_QDIOUP ; 
 int /*<<< orphan*/  atomic_clear_mask (int,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdio_shutdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (int /*<<< orphan*/ ,int,int) ; 

void zfcp_qdio_close(struct zfcp_qdio *qdio)
{
	struct zfcp_qdio_queue *req_q;
	int first, count;

	if (!(atomic_read(&qdio->adapter->status) & ZFCP_STATUS_ADAPTER_QDIOUP))
		return;

	/* clear QDIOUP flag, thus do_QDIO is not called during qdio_shutdown */
	req_q = &qdio->req_q;
	spin_lock_bh(&qdio->req_q_lock);
	atomic_clear_mask(ZFCP_STATUS_ADAPTER_QDIOUP, &qdio->adapter->status);
	spin_unlock_bh(&qdio->req_q_lock);

	wake_up(&qdio->req_q_wq);

	qdio_shutdown(qdio->adapter->ccw_device,
		      QDIO_FLAG_CLEANUP_USING_CLEAR);

	/* cleanup used outbound sbals */
	count = atomic_read(&req_q->count);
	if (count < QDIO_MAX_BUFFERS_PER_Q) {
		first = (req_q->first + count) % QDIO_MAX_BUFFERS_PER_Q;
		count = QDIO_MAX_BUFFERS_PER_Q - count;
		zfcp_qdio_zero_sbals(req_q->sbal, first, count);
	}
	req_q->first = 0;
	atomic_set(&req_q->count, 0);
	qdio->resp_q.first = 0;
	atomic_set(&qdio->resp_q.count, 0);
}