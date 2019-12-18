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
struct virtqueue {TYPE_1__* vdev; } ;
struct virtnet_info {int /*<<< orphan*/  napi; } ;
struct TYPE_2__ {struct virtnet_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  __napi_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ napi_schedule_prep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 

__attribute__((used)) static void skb_recv_done(struct virtqueue *rvq)
{
	struct virtnet_info *vi = rvq->vdev->priv;
	/* Schedule NAPI, Suppress further interrupts if successful. */
	if (napi_schedule_prep(&vi->napi)) {
		virtqueue_disable_cb(rvq);
		__napi_schedule(&vi->napi);
	}
}