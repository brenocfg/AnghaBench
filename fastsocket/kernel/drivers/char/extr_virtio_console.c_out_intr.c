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
struct port {int /*<<< orphan*/  waitqueue; } ;
struct TYPE_2__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 struct port* find_port_by_vq (int /*<<< orphan*/ ,struct virtqueue*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void out_intr(struct virtqueue *vq)
{
	struct port *port;

	port = find_port_by_vq(vq->vdev->priv, vq);
	if (!port)
		return;

	wake_up_interruptible(&port->waitqueue);
}