#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vhost_virtqueue {int num; int signalled_used_valid; int log_used; unsigned long long log_addr; int /*<<< orphan*/ * ubufs; scalar_t__ done_idx; scalar_t__ upend_idx; int /*<<< orphan*/ * log_ctx; int /*<<< orphan*/ * call; int /*<<< orphan*/ * call_ctx; int /*<<< orphan*/ * kick; int /*<<< orphan*/ * error; int /*<<< orphan*/ * error_ctx; int /*<<< orphan*/ * log_base; int /*<<< orphan*/ * private_data; scalar_t__ sock_hlen; scalar_t__ vhost_hlen; scalar_t__ used_flags; scalar_t__ signalled_used; scalar_t__ last_used_idx; scalar_t__ avail_idx; scalar_t__ last_avail_idx; int /*<<< orphan*/ * used; int /*<<< orphan*/ * avail; int /*<<< orphan*/ * desc; } ;
struct vhost_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void vhost_vq_reset(struct vhost_dev *dev,
			   struct vhost_virtqueue *vq)
{
	vq->num = 1;
	vq->desc = NULL;
	vq->avail = NULL;
	vq->used = NULL;
	vq->last_avail_idx = 0;
	vq->avail_idx = 0;
	vq->last_used_idx = 0;
	vq->signalled_used = 0;
	vq->signalled_used_valid = false;
	vq->used_flags = 0;
	vq->log_used = false;
	vq->log_addr = -1ull;
	vq->vhost_hlen = 0;
	vq->sock_hlen = 0;
	vq->private_data = NULL;
	vq->log_base = NULL;
	vq->error_ctx = NULL;
	vq->error = NULL;
	vq->kick = NULL;
	vq->call_ctx = NULL;
	vq->call = NULL;
	vq->log_ctx = NULL;
	vq->upend_idx = 0;
	vq->done_idx = 0;
	vq->ubufs = NULL;
}