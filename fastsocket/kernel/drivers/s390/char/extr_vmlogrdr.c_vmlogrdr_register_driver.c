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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/ * class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  driver_attr_recording_status ; 
 int driver_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_unregister (int /*<<< orphan*/ *) ; 
 int iucv_register (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  iucv_unregister (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vmlogrdr_class ; 
 int /*<<< orphan*/  vmlogrdr_driver ; 
 int /*<<< orphan*/  vmlogrdr_iucv_handler ; 

__attribute__((used)) static int vmlogrdr_register_driver(void)
{
	int ret;

	/* Register with iucv driver */
	ret = iucv_register(&vmlogrdr_iucv_handler, 1);
	if (ret)
		goto out;

	ret = driver_register(&vmlogrdr_driver);
	if (ret)
		goto out_iucv;

	ret = driver_create_file(&vmlogrdr_driver,
				 &driver_attr_recording_status);
	if (ret)
		goto out_driver;

	vmlogrdr_class = class_create(THIS_MODULE, "vmlogrdr");
	if (IS_ERR(vmlogrdr_class)) {
		ret = PTR_ERR(vmlogrdr_class);
		vmlogrdr_class = NULL;
		goto out_attr;
	}
	return 0;

out_attr:
	driver_remove_file(&vmlogrdr_driver, &driver_attr_recording_status);
out_driver:
	driver_unregister(&vmlogrdr_driver);
out_iucv:
	iucv_unregister(&vmlogrdr_iucv_handler, 1);
out:
	return ret;
}