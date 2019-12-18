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
struct uio_info {scalar_t__ irq; struct uio_device* uio_dev; } ;
struct uio_device {int /*<<< orphan*/  minor; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct uio_device*) ; 
 int /*<<< orphan*/  kfree (struct uio_device*) ; 
 TYPE_1__* uio_class ; 
 int /*<<< orphan*/  uio_class_destroy () ; 
 int /*<<< orphan*/  uio_dev_del_attributes (struct uio_device*) ; 
 int /*<<< orphan*/  uio_free_minor (struct uio_device*) ; 
 int /*<<< orphan*/  uio_major ; 

void uio_unregister_device(struct uio_info *info)
{
	struct uio_device *idev;

	if (!info || !info->uio_dev)
		return;

	idev = info->uio_dev;

	uio_free_minor(idev);

	if (info->irq >= 0)
		free_irq(info->irq, idev);

	uio_dev_del_attributes(idev);

	dev_set_drvdata(idev->dev, NULL);
	device_destroy(uio_class->class, MKDEV(uio_major, idev->minor));
	kfree(idev);
	uio_class_destroy();

	return;
}