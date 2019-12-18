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
struct iio_ring_buffer {int /*<<< orphan*/  access_dev; int /*<<< orphan*/  access_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_free_idr_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_ring_access_idr ; 

__attribute__((used)) static void __iio_free_ring_buffer_access_chrdev(struct iio_ring_buffer *buf)
{
	iio_free_idr_val(&iio_ring_access_idr, buf->access_id);
	device_unregister(&buf->access_dev);
}