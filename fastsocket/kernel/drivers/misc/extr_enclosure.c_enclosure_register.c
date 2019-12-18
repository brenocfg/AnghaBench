#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  parent; int /*<<< orphan*/ * class; } ;
struct enclosure_device {int components; TYPE_2__ edev; int /*<<< orphan*/  node; TYPE_1__* component; struct enclosure_component_callbacks* cb; } ;
struct enclosure_component_callbacks {int dummy; } ;
struct enclosure_component {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 struct enclosure_device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  container_list ; 
 int /*<<< orphan*/  container_list_lock ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,char const*) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  enclosure_class ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct enclosure_device*) ; 
 struct enclosure_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 

struct enclosure_device *
enclosure_register(struct device *dev, const char *name, int components,
		   struct enclosure_component_callbacks *cb)
{
	struct enclosure_device *edev =
		kzalloc(sizeof(struct enclosure_device) +
			sizeof(struct enclosure_component)*components,
			GFP_KERNEL);
	int err, i;

	BUG_ON(!cb);

	if (!edev)
		return ERR_PTR(-ENOMEM);

	edev->components = components;

	edev->edev.class = &enclosure_class;
	edev->edev.parent = get_device(dev);
	edev->cb = cb;
	dev_set_name(&edev->edev, "%s", name);
	err = device_register(&edev->edev);
	if (err)
		goto err;

	for (i = 0; i < components; i++)
		edev->component[i].number = -1;

	mutex_lock(&container_list_lock);
	list_add_tail(&edev->node, &container_list);
	mutex_unlock(&container_list_lock);

	return edev;

 err:
	put_device(edev->edev.parent);
	kfree(edev);
	return ERR_PTR(err);
}