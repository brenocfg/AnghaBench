#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev {TYPE_2__* ring; int /*<<< orphan*/  modes; } ;
struct TYPE_3__ {int /*<<< orphan*/ * get_bpd; int /*<<< orphan*/ * get_length; int /*<<< orphan*/ * rip_lots; } ;
struct TYPE_4__ {TYPE_1__ access; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_RING_HARDWARE_BUFFER ; 
 TYPE_2__* sca3000_rb_allocate (struct iio_dev*) ; 
 int /*<<< orphan*/  sca3000_ring_get_bpd ; 
 int /*<<< orphan*/  sca3000_ring_get_length ; 
 int /*<<< orphan*/  sca3000_rip_hw_rb ; 

int sca3000_configure_ring(struct iio_dev *indio_dev)
{
	indio_dev->ring = sca3000_rb_allocate(indio_dev);
	if (indio_dev->ring == NULL)
		return -ENOMEM;
	indio_dev->modes |= INDIO_RING_HARDWARE_BUFFER;

	indio_dev->ring->access.rip_lots = &sca3000_rip_hw_rb;
	indio_dev->ring->access.get_length = &sca3000_ring_get_length;
	indio_dev->ring->access.get_bpd = &sca3000_ring_get_bpd;

	return 0;
}