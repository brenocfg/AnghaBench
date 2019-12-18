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
struct device {int /*<<< orphan*/  parent; int /*<<< orphan*/  class; int /*<<< orphan*/ * type; } ;
struct hci_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  parent; int /*<<< orphan*/  type; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_class ; 
 int /*<<< orphan*/  bt_host ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct hci_dev*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int /*<<< orphan*/ ) ; 
 int device_register (struct device*) ; 

int hci_register_sysfs(struct hci_dev *hdev)
{
	struct device *dev = &hdev->dev;
	int err;

	BT_DBG("%p name %s type %d", hdev, hdev->name, hdev->type);

	dev->type = &bt_host;
	dev->class = bt_class;
	dev->parent = hdev->parent;

	dev_set_name(dev, "%s", hdev->name);

	dev_set_drvdata(dev, hdev);

	err = device_register(dev);
	if (err < 0)
		return err;

	return 0;
}