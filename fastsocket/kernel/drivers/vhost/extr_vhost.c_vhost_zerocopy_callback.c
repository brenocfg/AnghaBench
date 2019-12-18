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
struct vhost_virtqueue {TYPE_1__* heads; int /*<<< orphan*/  poll; } ;
struct vhost_ubuf_ref {int /*<<< orphan*/  kref; struct vhost_virtqueue* vq; } ;
struct ubuf_info {size_t desc; struct vhost_ubuf_ref* arg; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_DMA_DONE_LEN ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhost_poll_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhost_zerocopy_done_signal ; 

void vhost_zerocopy_callback(void *arg)
{
	struct ubuf_info *ubuf = arg;
	struct vhost_ubuf_ref *ubufs = ubuf->arg;
	struct vhost_virtqueue *vq = ubufs->vq;

	vhost_poll_queue(&vq->poll);
	/* set len = 1 to mark this desc buffers done DMA */
	vq->heads[ubuf->desc].len = VHOST_DMA_DONE_LEN;
	kref_put(&ubufs->kref, vhost_zerocopy_done_signal);
}