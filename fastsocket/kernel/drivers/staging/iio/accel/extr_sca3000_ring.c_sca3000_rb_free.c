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
 int /*<<< orphan*/  iio_put_ring_buffer (struct iio_ring_buffer*) ; 

__attribute__((used)) static inline void sca3000_rb_free(struct iio_ring_buffer *r)
{
	if (r)
		iio_put_ring_buffer(r);
}