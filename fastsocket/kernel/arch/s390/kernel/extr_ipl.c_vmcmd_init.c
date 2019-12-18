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
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int /*<<< orphan*/  firmware_kobj ; 
 TYPE_1__* kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmcmd_attr_group ; 
 TYPE_1__* vmcmd_kset ; 

__attribute__((used)) static int vmcmd_init(void)
{
	if (!MACHINE_IS_VM)
		return -ENOTSUPP;
	vmcmd_kset = kset_create_and_add("vmcmd", NULL, firmware_kobj);
	if (!vmcmd_kset)
		return -ENOMEM;
	return sysfs_create_group(&vmcmd_kset->kobj, &vmcmd_attr_group);
}