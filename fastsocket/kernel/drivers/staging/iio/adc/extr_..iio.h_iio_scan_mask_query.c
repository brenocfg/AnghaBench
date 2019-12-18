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
struct iio_dev {int scan_mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int IIO_MAX_SCAN_LENGTH ; 

__attribute__((used)) static inline int iio_scan_mask_query(struct iio_dev *dev_info, int bit)
{
	if (bit > IIO_MAX_SCAN_LENGTH)
		return -EINVAL;
	else
		return !!(dev_info->scan_mask & (1 << bit));
}