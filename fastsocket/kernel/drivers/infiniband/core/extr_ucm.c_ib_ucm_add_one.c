#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  kobj; int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/  devt; int /*<<< orphan*/  parent; int /*<<< orphan*/ * class; } ;
struct ib_ucm_device {int devnum; TYPE_5__ cdev; TYPE_1__ dev; struct ib_device* ib_dev; } ;
struct ib_device {int /*<<< orphan*/  dma_device; int /*<<< orphan*/  node_type; int /*<<< orphan*/  alloc_ucontext; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_UCM_BASE_DEV ; 
 int IB_UCM_MAX_DEVICES ; 
 scalar_t__ RDMA_TRANSPORT_IB ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 scalar_t__ cdev_add (TYPE_5__*,scalar_t__,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_5__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_class ; 
 int /*<<< orphan*/  dev_attr_ibdev ; 
 int /*<<< orphan*/  dev_map ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 scalar_t__ device_create_file (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int find_overflow_devnum () ; 
 int /*<<< orphan*/  ib_set_client_data (struct ib_device*,int /*<<< orphan*/ *,struct ib_ucm_device*) ; 
 int /*<<< orphan*/  ib_ucm_release_dev ; 
 int /*<<< orphan*/  kfree (struct ib_ucm_device*) ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char*,int) ; 
 struct ib_ucm_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ overflow_maj ; 
 int /*<<< orphan*/  overflow_map ; 
 scalar_t__ rdma_node_get_transport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucm_client ; 
 int /*<<< orphan*/  ucm_fops ; 

__attribute__((used)) static void ib_ucm_add_one(struct ib_device *device)
{
	int devnum;
	dev_t base;
	struct ib_ucm_device *ucm_dev;

	if (!device->alloc_ucontext ||
	    rdma_node_get_transport(device->node_type) != RDMA_TRANSPORT_IB)
		return;

	ucm_dev = kzalloc(sizeof *ucm_dev, GFP_KERNEL);
	if (!ucm_dev)
		return;

	ucm_dev->ib_dev = device;

	devnum = find_first_zero_bit(dev_map, IB_UCM_MAX_DEVICES);
	if (devnum >= IB_UCM_MAX_DEVICES) {
		devnum = find_overflow_devnum();
		if (devnum < 0)
			goto err;

		ucm_dev->devnum = devnum + IB_UCM_MAX_DEVICES;
		base = devnum + overflow_maj;
		set_bit(devnum, overflow_map);
	} else {
		ucm_dev->devnum = devnum;
		base = devnum + IB_UCM_BASE_DEV;
		set_bit(devnum, dev_map);
	}

	cdev_init(&ucm_dev->cdev, &ucm_fops);
	ucm_dev->cdev.owner = THIS_MODULE;
	kobject_set_name(&ucm_dev->cdev.kobj, "ucm%d", ucm_dev->devnum);
	if (cdev_add(&ucm_dev->cdev, base, 1))
		goto err;

	ucm_dev->dev.class = &cm_class;
	ucm_dev->dev.parent = device->dma_device;
	ucm_dev->dev.devt = ucm_dev->cdev.dev;
	ucm_dev->dev.release = ib_ucm_release_dev;
	dev_set_name(&ucm_dev->dev, "ucm%d", ucm_dev->devnum);
	if (device_register(&ucm_dev->dev))
		goto err_cdev;

	if (device_create_file(&ucm_dev->dev, &dev_attr_ibdev))
		goto err_dev;

	ib_set_client_data(device, &ucm_client, ucm_dev);
	return;

err_dev:
	device_unregister(&ucm_dev->dev);
err_cdev:
	cdev_del(&ucm_dev->cdev);
	if (ucm_dev->devnum < IB_UCM_MAX_DEVICES)
		clear_bit(devnum, dev_map);
	else
		clear_bit(devnum, overflow_map);
err:
	kfree(ucm_dev);
	return;
}