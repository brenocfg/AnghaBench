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
struct vhost_virtqueue {int done_idx; int upend_idx; TYPE_1__* heads; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int UIO_MAXIOV ; 
 scalar_t__ VHOST_DMA_CLEAR_LEN ; 
 scalar_t__ VHOST_DMA_DONE_LEN ; 
 int /*<<< orphan*/  vhost_add_used_and_signal (int /*<<< orphan*/ ,struct vhost_virtqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vhost_zerocopy_signal_used(struct vhost_virtqueue *vq)
{
	int i;
	int j = 0;

	for (i = vq->done_idx; i != vq->upend_idx; i = (i + 1) % UIO_MAXIOV) {
		if ((vq->heads[i].len == VHOST_DMA_DONE_LEN)) {
			vq->heads[i].len = VHOST_DMA_CLEAR_LEN;
			vhost_add_used_and_signal(vq->dev, vq,
						  vq->heads[i].id, 0);
			++j;
		} else
			break;
	}
	if (j)
		vq->done_idx = i;
	return j;
}