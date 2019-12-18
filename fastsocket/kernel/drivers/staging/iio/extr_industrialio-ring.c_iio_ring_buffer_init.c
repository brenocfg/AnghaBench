#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct iio_ring_buffer* private; } ;
struct TYPE_5__ {struct iio_ring_buffer* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* mark_param_change ) (struct iio_ring_buffer*) ;} ;
struct iio_ring_buffer {TYPE_3__ access_handler; TYPE_2__ ev_int; struct iio_dev* indio_dev; TYPE_1__ access; } ;
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct iio_ring_buffer*) ; 

void iio_ring_buffer_init(struct iio_ring_buffer *ring,
			  struct iio_dev *dev_info)
{
	if (ring->access.mark_param_change)
		ring->access.mark_param_change(ring);
	ring->indio_dev = dev_info;
	ring->ev_int.private = ring;
	ring->access_handler.private = ring;
}