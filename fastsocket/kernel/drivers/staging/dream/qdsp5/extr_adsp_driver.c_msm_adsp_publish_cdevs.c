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
struct msm_adsp_module {TYPE_1__ pdev; int /*<<< orphan*/  name; } ;
struct adsp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  adsp_class ; 
 int /*<<< orphan*/  adsp_create (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int adsp_device_count ; 
 scalar_t__ adsp_devices ; 
 int /*<<< orphan*/  adsp_devno ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,char*) ; 
 int /*<<< orphan*/  class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 

void msm_adsp_publish_cdevs(struct msm_adsp_module *modules, unsigned n)
{
	int rc;

	adsp_devices = kzalloc(sizeof(struct adsp_device) * n, GFP_KERNEL);
	if (!adsp_devices)
		return;

	adsp_class = class_create(THIS_MODULE, "adsp");
	if (IS_ERR(adsp_class))
		goto fail_create_class;

	rc = alloc_chrdev_region(&adsp_devno, 0, n, "adsp");
	if (rc < 0)
		goto fail_alloc_region;

	adsp_device_count = n;
	for (n = 0; n < adsp_device_count; n++) {
		adsp_create(adsp_devices + n,
			    modules[n].name, &modules[n].pdev.dev,
			    MKDEV(MAJOR(adsp_devno), n));
	}

	return;

fail_alloc_region:
	class_unregister(adsp_class);
fail_create_class:
	kfree(adsp_devices);
}