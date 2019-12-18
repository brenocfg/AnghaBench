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
struct iio_sw_ring_buffer {int update_needed; } ;
struct iio_ring_buffer {int dummy; } ;

/* Variables and functions */
 struct iio_sw_ring_buffer* iio_to_sw_ring (struct iio_ring_buffer*) ; 

int iio_mark_update_needed_sw_rb(struct iio_ring_buffer *r)
{
	struct iio_sw_ring_buffer *ring = iio_to_sw_ring(r);
	ring->update_needed = true;
	return 0;
}