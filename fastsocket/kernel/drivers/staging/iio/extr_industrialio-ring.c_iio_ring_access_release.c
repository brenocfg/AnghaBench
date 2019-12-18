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
struct TYPE_2__ {int /*<<< orphan*/  chrdev; } ;
struct iio_ring_buffer {TYPE_1__ access_handler; } ;
struct device {int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 struct iio_ring_buffer* access_dev_to_iio_ring_buffer (struct device*) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_device_free_chrdev_minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iio_ring_access_release(struct device *dev)
{
	struct iio_ring_buffer *buf
		= access_dev_to_iio_ring_buffer(dev);
	cdev_del(&buf->access_handler.chrdev);
	iio_device_free_chrdev_minor(MINOR(dev->devt));
}