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
struct iio_dev {TYPE_1__* ring; } ;
struct TYPE_2__ {int /*<<< orphan*/ * postdisable; int /*<<< orphan*/ * preenable; } ;

/* Variables and functions */
 int /*<<< orphan*/  sca3000_hw_ring_postdisable ; 
 int /*<<< orphan*/  sca3000_hw_ring_preenable ; 

void sca3000_register_ring_funcs(struct iio_dev *indio_dev)
{
	indio_dev->ring->preenable = &sca3000_hw_ring_preenable;
	indio_dev->ring->postdisable = &sca3000_hw_ring_postdisable;
}