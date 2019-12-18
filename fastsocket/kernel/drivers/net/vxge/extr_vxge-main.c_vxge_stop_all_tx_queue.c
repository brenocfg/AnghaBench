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
struct TYPE_4__ {scalar_t__ tx_steering_type; } ;
struct vxgedev {int no_of_vpath; TYPE_3__* vpaths; TYPE_1__ config; struct net_device* ndev; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  queue_state; } ;
struct TYPE_6__ {TYPE_2__ fifo; } ;

/* Variables and functions */
 scalar_t__ TX_MULTIQ_STEERING ; 
 int /*<<< orphan*/  VPATH_QUEUE_STOP ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 

void vxge_stop_all_tx_queue(struct vxgedev *vdev)
{
	int i;
	struct net_device *dev = vdev->ndev;

	if (vdev->config.tx_steering_type != TX_MULTIQ_STEERING) {
		for (i = 0; i < vdev->no_of_vpath; i++)
			vdev->vpaths[i].fifo.queue_state = VPATH_QUEUE_STOP;
	}
	netif_tx_stop_all_queues(dev);
}