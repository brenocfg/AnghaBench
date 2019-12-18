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
struct iio_sw_ring_buffer {int /*<<< orphan*/  use_lock; int /*<<< orphan*/  use_count; } ;
struct iio_ring_buffer {int dummy; } ;

/* Variables and functions */
 struct iio_sw_ring_buffer* iio_to_sw_ring (struct iio_ring_buffer*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void iio_mark_sw_rb_in_use(struct iio_ring_buffer *r)
{
	struct iio_sw_ring_buffer *ring = iio_to_sw_ring(r);
	spin_lock(&ring->use_lock);
	ring->use_count++;
	spin_unlock(&ring->use_lock);
}