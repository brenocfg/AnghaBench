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
struct virtio_device {int dummy; } ;
struct lguest_device_desc {unsigned int config_len; } ;
struct TYPE_2__ {struct lguest_device_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ lg_config (struct lguest_device_desc*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,unsigned int) ; 
 TYPE_1__* to_lgdev (struct virtio_device*) ; 

__attribute__((used)) static void lg_get(struct virtio_device *vdev, unsigned int offset,
		   void *buf, unsigned len)
{
	struct lguest_device_desc *desc = to_lgdev(vdev)->desc;

	/* Check they didn't ask for more than the length of the config! */
	BUG_ON(offset + len > desc->config_len);
	memcpy(buf, lg_config(desc) + offset, len);
}