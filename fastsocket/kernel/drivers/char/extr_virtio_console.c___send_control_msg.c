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
typedef  int /*<<< orphan*/  u32 ;
struct virtqueue {int dummy; } ;
struct virtio_console_control {unsigned int event; unsigned int value; int /*<<< orphan*/  id; } ;
struct scatterlist {int dummy; } ;
struct ports_device {int /*<<< orphan*/  c_ovq_lock; struct virtqueue* c_ovq; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  cpkt ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,struct virtio_console_control*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_multiport (struct ports_device*) ; 
 scalar_t__ virtqueue_add_buf (struct virtqueue*,struct scatterlist*,int,int /*<<< orphan*/ ,struct virtio_console_control*) ; 
 int /*<<< orphan*/  virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int /*<<< orphan*/  virtqueue_kick (struct virtqueue*) ; 

__attribute__((used)) static ssize_t __send_control_msg(struct ports_device *portdev, u32 port_id,
				  unsigned int event, unsigned int value)
{
	struct scatterlist sg[1];
	struct virtio_console_control cpkt;
	struct virtqueue *vq;
	unsigned int len;

	if (!use_multiport(portdev))
		return 0;

	cpkt.id = port_id;
	cpkt.event = event;
	cpkt.value = value;

	vq = portdev->c_ovq;

	sg_init_one(sg, &cpkt, sizeof(cpkt));

	spin_lock(&portdev->c_ovq_lock);
	if (virtqueue_add_buf(vq, sg, 1, 0, &cpkt) >= 0) {
		virtqueue_kick(vq);
		while (!virtqueue_get_buf(vq, &len))
			cpu_relax();
	}
	spin_unlock(&portdev->c_ovq_lock);
	return 0;
}