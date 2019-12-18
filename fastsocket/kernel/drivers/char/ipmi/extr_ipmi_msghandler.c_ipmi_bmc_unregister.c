#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct bmc_device {int /*<<< orphan*/  refcount; TYPE_3__* dev; } ;
typedef  TYPE_4__* ipmi_smi_t ;
struct TYPE_9__ {struct bmc_device* bmc; int /*<<< orphan*/ * my_dev_name; int /*<<< orphan*/ * sysfs_name; TYPE_1__* si_dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_8__ {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_bmc_device ; 
 int /*<<< orphan*/  ipmidriver_mutex ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipmi_bmc_unregister(ipmi_smi_t intf)
{
	struct bmc_device *bmc = intf->bmc;

	if (intf->sysfs_name) {
		sysfs_remove_link(&intf->si_dev->kobj, intf->sysfs_name);
		kfree(intf->sysfs_name);
		intf->sysfs_name = NULL;
	}
	if (intf->my_dev_name) {
		sysfs_remove_link(&bmc->dev->dev.kobj, intf->my_dev_name);
		kfree(intf->my_dev_name);
		intf->my_dev_name = NULL;
	}

	mutex_lock(&ipmidriver_mutex);
	kref_put(&bmc->refcount, cleanup_bmc_device);
	intf->bmc = NULL;
	mutex_unlock(&ipmidriver_mutex);
}