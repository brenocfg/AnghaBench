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
struct ports_device {TYPE_1__* vdev; } ;
struct TYPE_2__ {int* features; } ;

/* Variables and functions */
 int VIRTIO_CONSOLE_F_MULTIPORT ; 

__attribute__((used)) static inline bool use_multiport(struct ports_device *portdev)
{
	/*
	 * This condition can be true when put_chars is called from
	 * early_init
	 */
	if (!portdev->vdev)
		return 0;
	return portdev->vdev->features[0] & (1 << VIRTIO_CONSOLE_F_MULTIPORT);
}