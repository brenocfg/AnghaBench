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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_put () ; 
 int /*<<< orphan*/  kfree (struct iio_dev*) ; 
 struct iio_dev* to_iio_dev (struct device*) ; 

__attribute__((used)) static void iio_dev_release(struct device *device)
{
	struct iio_dev *dev = to_iio_dev(device);

	iio_put();
	kfree(dev);
}