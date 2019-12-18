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
 int iio_ring_buffer_register (struct iio_ring_buffer*) ; 

int max1363_initialize_ring(struct iio_ring_buffer *ring)
{
	return iio_ring_buffer_register(ring);
}