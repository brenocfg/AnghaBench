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

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IIO_DEV_MAX ; 
 int idr_get_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ idr_pre_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_chrdev_idr ; 
 int /*<<< orphan*/  iio_idr_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int iio_device_get_chrdev_minor(void)
{
	int ret, val;

idr_again:
	if (unlikely(idr_pre_get(&iio_chrdev_idr, GFP_KERNEL) == 0))
		return -ENOMEM;
	spin_lock(&iio_idr_lock);
	ret = idr_get_new(&iio_chrdev_idr, NULL, &val);
	spin_unlock(&iio_idr_lock);
	if (unlikely(ret == -EAGAIN))
		goto idr_again;
	else if (unlikely(ret))
		return ret;
	if (val > IIO_DEV_MAX)
		return -ENOMEM;
	return val;
}