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
struct virtio_balloon {int /*<<< orphan*/  stats; struct virtqueue* stats_vq; scalar_t__ need_stats_update; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_balloon_stats (struct virtio_balloon*) ; 
 scalar_t__ virtqueue_add_buf (struct virtqueue*,struct scatterlist*,int,int /*<<< orphan*/ ,struct virtio_balloon*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static void stats_handle_request(struct virtio_balloon *vb)
{
	struct virtqueue *vq;
	struct scatterlist sg;

	vb->need_stats_update = 0;
	update_balloon_stats(vb);

	vq = vb->stats_vq;
	sg_init_one(&sg, vb->stats, sizeof(vb->stats));
	if (virtqueue_add_buf(vq, &sg, 1, 0, vb) < 0)
		BUG();
	virtqueue_kick(vq);
}