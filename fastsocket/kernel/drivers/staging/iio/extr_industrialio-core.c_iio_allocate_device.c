#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * class; int /*<<< orphan*/ * type; } ;
struct iio_dev {int /*<<< orphan*/  mlock; TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  iio_class ; 
 int /*<<< orphan*/  iio_dev_type ; 
 int /*<<< orphan*/  iio_get () ; 
 struct iio_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

struct iio_dev *iio_allocate_device(void)
{
	struct iio_dev *dev = kzalloc(sizeof *dev, GFP_KERNEL);

	if (dev) {
		dev->dev.type = &iio_dev_type;
		dev->dev.class = &iio_class;
		device_initialize(&dev->dev);
		dev_set_drvdata(&dev->dev, (void *)dev);
		mutex_init(&dev->mlock);
		iio_get();
	}

	return dev;
}