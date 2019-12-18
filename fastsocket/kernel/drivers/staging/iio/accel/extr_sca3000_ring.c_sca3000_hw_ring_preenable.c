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
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int __sca3000_hw_ring_state_set (struct iio_dev*,int) ; 

__attribute__((used)) static int sca3000_hw_ring_preenable(struct iio_dev *indio_dev)
{
	return __sca3000_hw_ring_state_set(indio_dev, 1);
}