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
struct vmlogrdr_priv_t {struct device* device; int /*<<< orphan*/ * class_device; int /*<<< orphan*/  minor_num; int /*<<< orphan*/  internal_name; } ;
struct device {void (* release ) (struct device*) ;int /*<<< orphan*/  kobj; int /*<<< orphan*/ * driver; int /*<<< orphan*/  parent; int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct vmlogrdr_priv_t*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_create (int /*<<< orphan*/ ,struct device*,int /*<<< orphan*/ ,struct vmlogrdr_priv_t*,char*,int /*<<< orphan*/ ) ; 
 int device_register (struct device*) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  iucv_bus ; 
 int /*<<< orphan*/  iucv_root ; 
 scalar_t__ kfree ; 
 struct device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmlogrdr_attr_group ; 
 int /*<<< orphan*/  vmlogrdr_class ; 
 int /*<<< orphan*/  vmlogrdr_driver ; 
 int /*<<< orphan*/  vmlogrdr_major ; 

__attribute__((used)) static int vmlogrdr_register_device(struct vmlogrdr_priv_t *priv)
{
	struct device *dev;
	int ret;

	dev = kzalloc(sizeof(struct device), GFP_KERNEL);
	if (dev) {
		dev_set_name(dev, priv->internal_name);
		dev->bus = &iucv_bus;
		dev->parent = iucv_root;
		dev->driver = &vmlogrdr_driver;
		dev_set_drvdata(dev, priv);
		/*
		 * The release function could be called after the
		 * module has been unloaded. It's _only_ task is to
		 * free the struct. Therefore, we specify kfree()
		 * directly here. (Probably a little bit obfuscating
		 * but legitime ...).
		 */
		dev->release = (void (*)(struct device *))kfree;
	} else
		return -ENOMEM;
	ret = device_register(dev);
	if (ret) {
		put_device(dev);
		return ret;
	}

	ret = sysfs_create_group(&dev->kobj, &vmlogrdr_attr_group);
	if (ret) {
		device_unregister(dev);
		return ret;
	}
	priv->class_device = device_create(vmlogrdr_class, dev,
					   MKDEV(vmlogrdr_major,
						 priv->minor_num),
					   priv, "%s", dev_name(dev));
	if (IS_ERR(priv->class_device)) {
		ret = PTR_ERR(priv->class_device);
		priv->class_device=NULL;
		sysfs_remove_group(&dev->kobj, &vmlogrdr_attr_group);
		device_unregister(dev);
		return ret;
	}
	priv->device = dev;
	return 0;
}