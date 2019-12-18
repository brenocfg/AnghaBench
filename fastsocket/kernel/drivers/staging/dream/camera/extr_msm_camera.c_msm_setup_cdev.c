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
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct msm_device {TYPE_1__ cdev; } ;
struct file_operations {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,struct file_operations const*) ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,int) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_class ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int msm_setup_cdev(struct msm_device *msm,
			int node,
			dev_t devno,
			const char *suffix,
			const struct file_operations *fops)
{
	int rc = -ENODEV;

	struct device *device =
		device_create(msm_class, NULL,
			devno, NULL,
			"%s%d", suffix, node);

	if (IS_ERR(device)) {
		rc = PTR_ERR(device);
		pr_err("msm_camera: error creating device: %d\n", rc);
		return rc;
	}

	cdev_init(&msm->cdev, fops);
	msm->cdev.owner = THIS_MODULE;

	rc = cdev_add(&msm->cdev, devno, 1);
	if (rc < 0) {
		pr_err("msm_camera: error adding cdev: %d\n", rc);
		device_destroy(msm_class, devno);
		return rc;
	}

	return rc;
}