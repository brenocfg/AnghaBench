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
struct vio_dring_state {unsigned int cons; } ;
struct TYPE_5__ {scalar_t__ state; } ;
struct vio_disk_desc {int /*<<< orphan*/  size; scalar_t__ status; TYPE_2__ hdr; int /*<<< orphan*/  ncookies; int /*<<< orphan*/  cookies; } ;
struct vdc_req_entry {struct request* req; } ;
struct TYPE_4__ {int /*<<< orphan*/  lp; } ;
struct vdc_port {TYPE_3__* disk; TYPE_1__ vio; struct vdc_req_entry* rq_arr; } ;
struct request {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int VDC_TX_RING_SIZE ; 
 scalar_t__ VIO_DESC_DONE ; 
 scalar_t__ VIO_DESC_FREE ; 
 int /*<<< orphan*/  __blk_end_request (struct request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_start_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldc_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vdc_end_special (struct vdc_port*,struct vio_disk_desc*) ; 
 struct vio_disk_desc* vio_dring_entry (struct vio_dring_state*,unsigned int) ; 

__attribute__((used)) static void vdc_end_one(struct vdc_port *port, struct vio_dring_state *dr,
			unsigned int index)
{
	struct vio_disk_desc *desc = vio_dring_entry(dr, index);
	struct vdc_req_entry *rqe = &port->rq_arr[index];
	struct request *req;

	if (unlikely(desc->hdr.state != VIO_DESC_DONE))
		return;

	ldc_unmap(port->vio.lp, desc->cookies, desc->ncookies);
	desc->hdr.state = VIO_DESC_FREE;
	dr->cons = (index + 1) & (VDC_TX_RING_SIZE - 1);

	req = rqe->req;
	if (req == NULL) {
		vdc_end_special(port, desc);
		return;
	}

	rqe->req = NULL;

	__blk_end_request(req, (desc->status ? -EIO : 0), desc->size);

	if (blk_queue_stopped(port->disk->queue))
		blk_start_queue(port->disk->queue);
}