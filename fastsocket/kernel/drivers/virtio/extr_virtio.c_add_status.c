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
struct virtio_device {TYPE_1__* config; } ;
struct TYPE_2__ {unsigned int (* get_status ) (struct virtio_device*) ;int /*<<< orphan*/  (* set_status ) (struct virtio_device*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct virtio_device*,unsigned int) ; 
 unsigned int stub2 (struct virtio_device*) ; 

__attribute__((used)) static void add_status(struct virtio_device *dev, unsigned status)
{
	dev->config->set_status(dev, dev->config->get_status(dev) | status);
}