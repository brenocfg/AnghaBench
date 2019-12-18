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
struct vhost_virtqueue {int signalled_used_valid; TYPE_1__* used; int /*<<< orphan*/  last_used_idx; int /*<<< orphan*/  private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int get_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vhost_update_used_flags (struct vhost_virtqueue*) ; 

int vhost_init_used(struct vhost_virtqueue *vq)
{
	int r;
	if (!vq->private_data)
		return 0;

	r = vhost_update_used_flags(vq);
	if (r)
		return r;
	vq->signalled_used_valid = false;
	return get_user(vq->last_used_idx, &vq->used->idx);
}