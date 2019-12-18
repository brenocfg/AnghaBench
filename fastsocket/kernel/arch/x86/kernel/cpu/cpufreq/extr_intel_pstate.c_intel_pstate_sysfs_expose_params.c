#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ kset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 TYPE_2__ cpu_sysdev_class ; 
 int /*<<< orphan*/  intel_pstate_attr_group ; 
 int /*<<< orphan*/  intel_pstate_kobject ; 
 int /*<<< orphan*/  kobject_create_and_add (char*,int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_pstate_sysfs_expose_params(void)
{
	int rc;

	intel_pstate_kobject = kobject_create_and_add("intel_pstate",
						&cpu_sysdev_class.kset.kobj);

	BUG_ON(!intel_pstate_kobject);
	rc = sysfs_create_group(intel_pstate_kobject,
				&intel_pstate_attr_group);
	BUG_ON(rc);
}