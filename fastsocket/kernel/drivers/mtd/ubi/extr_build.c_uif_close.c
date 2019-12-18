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
struct ubi_device {scalar_t__ vtbl_slots; TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (TYPE_1__*) ; 
 int /*<<< orphan*/  kill_volumes (struct ubi_device*) ; 
 int /*<<< orphan*/  ubi_sysfs_close (struct ubi_device*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void uif_close(struct ubi_device *ubi)
{
	kill_volumes(ubi);
	ubi_sysfs_close(ubi);
	cdev_del(&ubi->cdev);
	unregister_chrdev_region(ubi->cdev.dev, ubi->vtbl_slots + 1);
}