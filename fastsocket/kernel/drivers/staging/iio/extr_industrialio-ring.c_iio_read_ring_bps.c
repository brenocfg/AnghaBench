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
struct TYPE_2__ {int (* get_bpd ) (struct iio_ring_buffer*) ;} ;
struct iio_ring_buffer {TYPE_1__ access; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct iio_ring_buffer* dev_get_drvdata (struct device*) ; 
 int sprintf (char*,char*,int) ; 
 int stub1 (struct iio_ring_buffer*) ; 
 int stub2 (struct iio_ring_buffer*) ; 

ssize_t iio_read_ring_bps(struct device *dev,
			  struct device_attribute *attr,
			  char *buf)
{
	int len = 0;
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);

	if (ring->access.get_bpd)
		len = sprintf(buf, "%d\n",
			      ring->access.get_bpd(ring));

	return len;
}