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
struct vring_used_elem {int dummy; } ;
struct vhost_virtqueue {int dummy; } ;
struct vhost_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_add_used_n (struct vhost_virtqueue*,struct vring_used_elem*,unsigned int) ; 
 int /*<<< orphan*/  vhost_signal (struct vhost_dev*,struct vhost_virtqueue*) ; 

void vhost_add_used_and_signal_n(struct vhost_dev *dev,
				 struct vhost_virtqueue *vq,
				 struct vring_used_elem *heads, unsigned count)
{
	vhost_add_used_n(vq, heads, count);
	vhost_signal(dev, vq);
}