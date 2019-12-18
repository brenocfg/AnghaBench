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
struct virtnet_info {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct virtnet_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 

__attribute__((used)) static void skb_xmit_done(struct virtqueue *svq)
{
	struct virtnet_info *vi = svq->vdev->priv;

	/* Suppress further interrupts. */
	virtqueue_disable_cb(svq);

	/* We were probably waiting for more output buffers. */
	netif_wake_queue(vi->dev);
}