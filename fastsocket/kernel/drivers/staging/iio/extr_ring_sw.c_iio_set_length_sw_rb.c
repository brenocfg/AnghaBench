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
struct TYPE_2__ {int /*<<< orphan*/  (* mark_param_change ) (struct iio_ring_buffer*) ;} ;
struct iio_ring_buffer {int length; TYPE_1__ access; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct iio_ring_buffer*) ; 

int iio_set_length_sw_rb(struct iio_ring_buffer *r, int length)
{
	if (r->length != length) {
		r->length = length;
		if (r->access.mark_param_change)
			r->access.mark_param_change(r);
	}
	return 0;
}