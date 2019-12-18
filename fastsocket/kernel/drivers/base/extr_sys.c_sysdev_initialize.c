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
struct sysdev_class {int /*<<< orphan*/  kset; } ;
struct TYPE_3__ {int /*<<< orphan*/ * kset; } ;
struct sys_device {TYPE_1__ kobj; struct sysdev_class* cls; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  kobject_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktype_sysdev ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

int sysdev_initialize(struct sys_device *sysdev)
{
	struct sysdev_class *cls = sysdev->cls;

	if (!cls)
		return -EINVAL;

	/* initialize the kobject to 0, in case it had previously been used */
	memset(&sysdev->kobj, 0x00, sizeof(struct kobject));

	/* Make sure the kset is set */
	sysdev->kobj.kset = &cls->kset;

	/* Register the object */
	kobject_init(&sysdev->kobj, &ktype_sysdev);

	return 0;
}