#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_device {TYPE_2__* ap_dev; int /*<<< orphan*/  list; TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_3__ device; } ;
struct TYPE_4__ {scalar_t__ rng; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_device_attr_group ; 
 int /*<<< orphan*/  zcrypt_device_count ; 
 int /*<<< orphan*/  zcrypt_device_lock ; 
 int /*<<< orphan*/  zcrypt_device_put (struct zcrypt_device*) ; 
 int /*<<< orphan*/  zcrypt_rng_device_remove () ; 

void zcrypt_device_unregister(struct zcrypt_device *zdev)
{
	if (zdev->ops->rng)
		zcrypt_rng_device_remove();
	spin_lock_bh(&zcrypt_device_lock);
	zcrypt_device_count--;
	list_del_init(&zdev->list);
	spin_unlock_bh(&zcrypt_device_lock);
	sysfs_remove_group(&zdev->ap_dev->device.kobj,
			   &zcrypt_device_attr_group);
	put_device(&zdev->ap_dev->device);
	zcrypt_device_put(zdev);
}