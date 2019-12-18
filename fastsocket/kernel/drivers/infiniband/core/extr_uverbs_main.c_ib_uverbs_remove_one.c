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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ib_uverbs_device {scalar_t__ devnum; int /*<<< orphan*/  comp; int /*<<< orphan*/  ref; TYPE_1__ cdev; int /*<<< orphan*/  dev; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IB_UVERBS_MAX_DEVICES ; 
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_map ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ib_uverbs_device* ib_get_client_data (struct ib_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_uverbs_release_dev ; 
 int /*<<< orphan*/  kfree (struct ib_uverbs_device*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  overflow_map ; 
 int /*<<< orphan*/  uverbs_class ; 
 int /*<<< orphan*/  uverbs_client ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ib_uverbs_remove_one(struct ib_device *device)
{
	struct ib_uverbs_device *uverbs_dev = ib_get_client_data(device, &uverbs_client);

	if (!uverbs_dev)
		return;

	dev_set_drvdata(uverbs_dev->dev, NULL);
	device_destroy(uverbs_class, uverbs_dev->cdev.dev);
	cdev_del(&uverbs_dev->cdev);

	if (uverbs_dev->devnum < IB_UVERBS_MAX_DEVICES)
		clear_bit(uverbs_dev->devnum, dev_map);
	else
		clear_bit(uverbs_dev->devnum - IB_UVERBS_MAX_DEVICES, overflow_map);

	kref_put(&uverbs_dev->ref, ib_uverbs_release_dev);
	wait_for_completion(&uverbs_dev->comp);
	kfree(uverbs_dev);
}