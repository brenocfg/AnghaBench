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
struct iio_ring_buffer {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_to_hw_ring_buf (struct iio_ring_buffer*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct iio_ring_buffer* to_iio_ring_buffer (struct device*) ; 

__attribute__((used)) static void sca3000_ring_release(struct device *dev)
{
	struct iio_ring_buffer *r = to_iio_ring_buffer(dev);
	kfree(iio_to_hw_ring_buf(r));
}