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
struct inode {int dummy; } ;
struct file {struct adsp_device* private_data; } ;
struct adsp_device {TYPE_1__* module; scalar_t__ abort; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  pmem_regions_lock; int /*<<< orphan*/  pmem_regions; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adsp_ops ; 
 struct adsp_device* inode_to_device (struct inode*) ; 
 int msm_adsp_get (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *,struct adsp_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int adsp_open(struct inode *inode, struct file *filp)
{
	struct adsp_device *adev;
	int rc;

	rc = nonseekable_open(inode, filp);
	if (rc < 0)
		return rc;

	adev = inode_to_device(inode);
	if (!adev)
		return -ENODEV;

	pr_info("adsp_open() name = '%s'\n", adev->name);

	rc = msm_adsp_get(adev->name, &adev->module, &adsp_ops, adev);
	if (rc)
		return rc;

	pr_info("adsp_open() module '%s' adev %p\n", adev->name, adev);
	filp->private_data = adev;
	adev->abort = 0;
	INIT_HLIST_HEAD(&adev->module->pmem_regions);
	mutex_init(&adev->module->pmem_regions_lock);

	return 0;
}