#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zcrypt_device {int online; TYPE_2__* ap_dev; int /*<<< orphan*/  list; TYPE_1__* ops; int /*<<< orphan*/  refcount; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_3__ device; int /*<<< orphan*/  qid; } ;
struct TYPE_5__ {scalar_t__ rng; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_INFO ; 
 int ENODEV ; 
 int /*<<< orphan*/  ZCRYPT_DBF_DEV (int /*<<< orphan*/ ,struct zcrypt_device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __zcrypt_increase_preference (struct zcrypt_device*) ; 
 int /*<<< orphan*/  get_device (TYPE_3__*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_device_attr_group ; 
 int /*<<< orphan*/  zcrypt_device_count ; 
 int /*<<< orphan*/  zcrypt_device_list ; 
 int /*<<< orphan*/  zcrypt_device_lock ; 
 int /*<<< orphan*/  zcrypt_device_put (struct zcrypt_device*) ; 
 int zcrypt_rng_device_add () ; 

int zcrypt_device_register(struct zcrypt_device *zdev)
{
	int rc;

	if (!zdev->ops)
		return -ENODEV;
	rc = sysfs_create_group(&zdev->ap_dev->device.kobj,
				&zcrypt_device_attr_group);
	if (rc)
		goto out;
	get_device(&zdev->ap_dev->device);
	kref_init(&zdev->refcount);
	spin_lock_bh(&zcrypt_device_lock);
	zdev->online = 1;	/* New devices are online by default. */
	ZCRYPT_DBF_DEV(DBF_INFO, zdev, "dev%04xo%dreg", zdev->ap_dev->qid,
		       zdev->online);
	list_add_tail(&zdev->list, &zcrypt_device_list);
	__zcrypt_increase_preference(zdev);
	zcrypt_device_count++;
	spin_unlock_bh(&zcrypt_device_lock);
	if (zdev->ops->rng) {
		rc = zcrypt_rng_device_add();
		if (rc)
			goto out_unregister;
	}
	return 0;

out_unregister:
	spin_lock_bh(&zcrypt_device_lock);
	zcrypt_device_count--;
	list_del_init(&zdev->list);
	spin_unlock_bh(&zcrypt_device_lock);
	sysfs_remove_group(&zdev->ap_dev->device.kobj,
			   &zcrypt_device_attr_group);
	put_device(&zdev->ap_dev->device);
	zcrypt_device_put(zdev);
out:
	return rc;
}