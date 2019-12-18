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
struct TYPE_2__ {int /*<<< orphan*/  length; int /*<<< orphan*/  bpd; } ;
struct iio_sw_ring_buffer {int /*<<< orphan*/  use_lock; TYPE_1__ buf; scalar_t__ use_count; int /*<<< orphan*/  update_needed; } ;
struct iio_ring_buffer {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  __iio_free_sw_ring_buffer (struct iio_sw_ring_buffer*) ; 
 int __iio_init_sw_ring_buffer (struct iio_sw_ring_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_sw_ring_buffer* iio_to_sw_ring (struct iio_ring_buffer*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int iio_request_update_sw_rb(struct iio_ring_buffer *r)
{
	int ret = 0;
	struct iio_sw_ring_buffer *ring = iio_to_sw_ring(r);

	spin_lock(&ring->use_lock);
	if (!ring->update_needed)
		goto error_ret;
	if (ring->use_count) {
		ret = -EAGAIN;
		goto error_ret;
	}
	__iio_free_sw_ring_buffer(ring);
	ret = __iio_init_sw_ring_buffer(ring, ring->buf.bpd, ring->buf.length);
error_ret:
	spin_unlock(&ring->use_lock);
	return ret;
}