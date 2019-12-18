#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zfcp_queue_req {int sbal_first; int sbal_number; } ;
struct zfcp_qdio_queue {int first; int /*<<< orphan*/  count; int /*<<< orphan*/  sbal; } ;
struct zfcp_qdio {TYPE_1__* adapter; struct zfcp_qdio_queue req_q; } ;
struct TYPE_2__ {int /*<<< orphan*/  ccw_device; } ;

/* Variables and functions */
 unsigned int QDIO_FLAG_SYNC_OUTPUT ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int do_QDIO (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_qdio_account (struct zfcp_qdio*) ; 
 int /*<<< orphan*/  zfcp_qdio_zero_sbals (int /*<<< orphan*/ ,int,int) ; 

int zfcp_qdio_send(struct zfcp_qdio *qdio, struct zfcp_queue_req *q_req)
{
	struct zfcp_qdio_queue *req_q = &qdio->req_q;
	int first = q_req->sbal_first;
	int count = q_req->sbal_number;
	int retval;
	unsigned int qdio_flags = QDIO_FLAG_SYNC_OUTPUT;

	zfcp_qdio_account(qdio);

	retval = do_QDIO(qdio->adapter->ccw_device, qdio_flags, 0, first,
			 count);
	if (unlikely(retval)) {
		zfcp_qdio_zero_sbals(req_q->sbal, first, count);
		return retval;
	}

	/* account for transferred buffers */
	atomic_sub(count, &req_q->count);
	req_q->first += count;
	req_q->first %= QDIO_MAX_BUFFERS_PER_Q;
	return 0;
}