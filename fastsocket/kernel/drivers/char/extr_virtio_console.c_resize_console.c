#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtio_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ws; int /*<<< orphan*/  hvc; } ;
struct port {TYPE_2__ cons; TYPE_1__* portdev; } ;
struct TYPE_3__ {struct virtio_device* vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTIO_CONSOLE_F_SIZE ; 
 int /*<<< orphan*/  hvc_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_console_port (struct port*) ; 
 scalar_t__ virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void resize_console(struct port *port)
{
	struct virtio_device *vdev;

	/* The port could have been hot-unplugged */
	if (!port || !is_console_port(port))
		return;

	vdev = port->portdev->vdev;
	if (virtio_has_feature(vdev, VIRTIO_CONSOLE_F_SIZE))
		hvc_resize(port->cons.hvc, port->cons.ws);
}