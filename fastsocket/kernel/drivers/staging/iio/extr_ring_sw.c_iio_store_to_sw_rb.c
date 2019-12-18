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
typedef  int /*<<< orphan*/  u8 ;
struct iio_sw_ring_buffer {int dummy; } ;
struct iio_ring_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int iio_store_to_sw_ring (struct iio_sw_ring_buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iio_sw_ring_buffer* iio_to_sw_ring (struct iio_ring_buffer*) ; 

int iio_store_to_sw_rb(struct iio_ring_buffer *r, u8 *data, s64 timestamp)
{
	struct iio_sw_ring_buffer *ring = iio_to_sw_ring(r);
	return iio_store_to_sw_ring(ring, data, timestamp);
}