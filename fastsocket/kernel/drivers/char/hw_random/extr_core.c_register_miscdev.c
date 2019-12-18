#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  this_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_rng_available ; 
 int /*<<< orphan*/  dev_attr_rng_current ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (TYPE_1__*) ; 
 int misc_register (TYPE_1__*) ; 
 TYPE_1__ rng_miscdev ; 

__attribute__((used)) static int register_miscdev(void)
{
	int err;

	err = misc_register(&rng_miscdev);
	if (err)
		goto out;
	err = device_create_file(rng_miscdev.this_device,
				 &dev_attr_rng_current);
	if (err)
		goto err_misc_dereg;
	err = device_create_file(rng_miscdev.this_device,
				 &dev_attr_rng_available);
	if (err)
		goto err_remove_current;
out:
	return err;

err_remove_current:
	device_remove_file(rng_miscdev.this_device, &dev_attr_rng_current);
err_misc_dereg:
	misc_deregister(&rng_miscdev);
	goto out;
}