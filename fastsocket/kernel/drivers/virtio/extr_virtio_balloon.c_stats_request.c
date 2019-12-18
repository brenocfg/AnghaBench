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
struct virtqueue {int dummy; } ;
struct virtio_balloon {int need_stats_update; int /*<<< orphan*/  config_change; } ;

/* Variables and functions */
 struct virtio_balloon* virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stats_request(struct virtqueue *vq)
{
	struct virtio_balloon *vb;
	unsigned int len;

	vb = virtqueue_get_buf(vq, &len);
	if (!vb)
		return;
	vb->need_stats_update = 1;
	wake_up(&vb->config_change);
}