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
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cap_devices ; 
 int /*<<< orphan*/  cap_major ; 
 int /*<<< orphan*/  cap_minor ; 
 int cap_nr_devs ; 
 int /*<<< orphan*/  cap_trim (TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cap_cleanup_module(void)
{
	int i;
	dev_t devno = MKDEV(cap_major, cap_minor);
	if (cap_devices) {
		for (i = 0; i < cap_nr_devs; i++) {
			cap_trim(cap_devices + i);
			cdev_del(&cap_devices[i].cdev);
		}
		kfree(cap_devices);
	}
	unregister_chrdev_region(devno, cap_nr_devs);

}