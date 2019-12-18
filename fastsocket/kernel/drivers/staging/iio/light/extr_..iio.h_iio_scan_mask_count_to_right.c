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

__attribute__((used)) static inline int iio_scan_mask_count_to_right(struct iio_dev *dev_info,
int bit)
{
	int count = 0;
	int mask = (1 << bit);
	if (bit > IIO_MAX_SCAN_LENGTH)
		return -EINVAL;
	while (mask) {
		mask >>= 1;
		if (mask & dev_info->scan_mask)
			count++;
	}

	return count;
}