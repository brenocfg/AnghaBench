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
typedef  scalar_t__ ulong ;
struct TYPE_2__ {scalar_t__ (* get_length ) (struct iio_ring_buffer*) ;int /*<<< orphan*/  (* mark_param_change ) (struct iio_ring_buffer*) ;int /*<<< orphan*/  (* set_length ) (struct iio_ring_buffer*,scalar_t__) ;} ;
struct iio_ring_buffer {TYPE_1__ access; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct iio_ring_buffer* dev_get_drvdata (struct device*) ; 
 int strict_strtoul (char const*,int,scalar_t__*) ; 
 scalar_t__ stub1 (struct iio_ring_buffer*) ; 
 int /*<<< orphan*/  stub2 (struct iio_ring_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct iio_ring_buffer*) ; 

ssize_t iio_write_ring_length(struct device *dev,
			       struct device_attribute *attr,
			       const char *buf,
			       size_t len)
{
	int ret;
	ulong val;
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	ret = strict_strtoul(buf, 10, &val);
	if (ret)
		return ret;

	if (ring->access.get_length)
		if (val == ring->access.get_length(ring))
			return len;

	if (ring->access.set_length) {
		ring->access.set_length(ring, val);
		if (ring->access.mark_param_change)
			ring->access.mark_param_change(ring);
	}

	return len;
}