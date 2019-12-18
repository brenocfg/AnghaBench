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
struct iio_ring_buffer {int id; int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iio_free_ring_buffer_event_chrdev (struct iio_ring_buffer*) ; 
 int __iio_request_ring_buffer_access_chrdev (struct iio_ring_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __iio_request_ring_buffer_event_chrdev (struct iio_ring_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_name (int /*<<< orphan*/ *,char*,int) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_free_idr_val (int /*<<< orphan*/ *,int) ; 
 int iio_get_new_idr_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_ring_idr ; 

int iio_ring_buffer_register(struct iio_ring_buffer *ring)
{
	int ret;
	ret = iio_get_new_idr_val(&iio_ring_idr);
	if (ret < 0)
		goto error_ret;
	else
		ring->id = ret;

	dev_set_name(&ring->dev, "ring_buffer%d", ring->id);
	ret = device_add(&ring->dev);
	if (ret)
		goto error_free_id;

	ret = __iio_request_ring_buffer_event_chrdev(ring,
						     0,
						     ring->owner,
						     &ring->dev);
	if (ret)
		goto error_remove_device;

	ret = __iio_request_ring_buffer_access_chrdev(ring,
						      0,
						      ring->owner);

	if (ret)
		goto error_free_ring_buffer_event_chrdev;

	return ret;
error_free_ring_buffer_event_chrdev:
	__iio_free_ring_buffer_event_chrdev(ring);
error_remove_device:
	device_del(&ring->dev);
error_free_id:
	iio_free_idr_val(&iio_ring_idr, ring->id);
error_ret:
	return ret;
}