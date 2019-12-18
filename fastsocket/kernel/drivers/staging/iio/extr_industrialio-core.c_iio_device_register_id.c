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
struct iio_dev {scalar_t__ id; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 scalar_t__ iio_get_new_idr_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iio_idr ; 

__attribute__((used)) static int iio_device_register_id(struct iio_dev *dev_info,
				  struct idr *this_idr)
{

	dev_info->id = iio_get_new_idr_val(&iio_idr);
	if (dev_info->id < 0)
		return dev_info->id;
	return 0;
}