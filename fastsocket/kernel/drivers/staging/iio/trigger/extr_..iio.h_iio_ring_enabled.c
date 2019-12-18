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
struct iio_dev {int currentmode; } ;

/* Variables and functions */
 int INDIO_RING_HARDWARE_BUFFER ; 
 int INDIO_RING_TRIGGERED ; 

__attribute__((used)) static inline bool iio_ring_enabled(struct iio_dev *dev_info)
{
	return dev_info->currentmode
		& (INDIO_RING_TRIGGERED
		   | INDIO_RING_HARDWARE_BUFFER);
}