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

/* Variables and functions */
 int iio_read_last_from_sw_ring (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  iio_to_sw_ring (struct iio_ring_buffer*) ; 

int iio_read_last_from_sw_rb(struct iio_ring_buffer *r,
			     unsigned char *data)
{
	return iio_read_last_from_sw_ring(iio_to_sw_ring(r), data);
}