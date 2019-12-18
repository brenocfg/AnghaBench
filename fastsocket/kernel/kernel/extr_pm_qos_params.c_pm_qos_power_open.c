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
struct file {void* private_data; } ;
struct TYPE_2__ {int pid; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  PM_QOS_DEFAULT_VALUE ; 
 TYPE_1__* current ; 
 long find_pm_qos_object_by_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iminor (struct inode*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  name ; 
 int pm_qos_add_requirement (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int pm_qos_power_open(struct inode *inode, struct file *filp)
{
	int ret;
	long pm_qos_class;

	lock_kernel();
	pm_qos_class = find_pm_qos_object_by_minor(iminor(inode));
	if (pm_qos_class >= 0) {
		filp->private_data = (void *)pm_qos_class;
		sprintf(name, "process_%d", current->pid);
		ret = pm_qos_add_requirement(pm_qos_class, name,
					PM_QOS_DEFAULT_VALUE);
		if (ret >= 0) {
			unlock_kernel();
			return 0;
		}
	}
	unlock_kernel();

	return -EPERM;
}