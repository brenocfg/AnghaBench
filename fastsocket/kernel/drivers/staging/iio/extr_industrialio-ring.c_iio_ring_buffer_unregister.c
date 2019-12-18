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
struct iio_ring_buffer {int /*<<< orphan*/  id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iio_free_ring_buffer_access_chrdev (struct iio_ring_buffer*) ; 
 int /*<<< orphan*/  __iio_free_ring_buffer_event_chrdev (struct iio_ring_buffer*) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_free_idr_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_ring_idr ; 

void iio_ring_buffer_unregister(struct iio_ring_buffer *ring)
{
	__iio_free_ring_buffer_access_chrdev(ring);
	__iio_free_ring_buffer_event_chrdev(ring);
	device_del(&ring->dev);
	iio_free_idr_val(&iio_ring_idr, ring->id);
}