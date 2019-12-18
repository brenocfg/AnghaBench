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
struct nvme_dev {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_list ; 
 int /*<<< orphan*/  dev_list_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int nvme_configure_admin_queue (struct nvme_dev*) ; 
 int nvme_dev_map (struct nvme_dev*) ; 
 int /*<<< orphan*/  nvme_dev_unmap (struct nvme_dev*) ; 
 int nvme_setup_io_queues (struct nvme_dev*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvme_dev_start(struct nvme_dev *dev)
{
	int result;

	result = nvme_dev_map(dev);
	if (result)
		return result;

	result = nvme_configure_admin_queue(dev);
	if (result)
		goto unmap;

	spin_lock(&dev_list_lock);
	list_add(&dev->node, &dev_list);
	spin_unlock(&dev_list_lock);

	result = nvme_setup_io_queues(dev);
	if (result && result != -EBUSY)
		goto disable;

	return result;

 disable:
	spin_lock(&dev_list_lock);
	list_del_init(&dev->node);
	spin_unlock(&dev_list_lock);
 unmap:
	nvme_dev_unmap(dev);
	return result;
}