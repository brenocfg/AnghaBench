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
struct mem_ctl_info {int /*<<< orphan*/ * mc_driver_sysfs_attributes; } ;
struct TYPE_2__ {int x86; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * amd64_dbg_attrs ; 
 int /*<<< orphan*/ * amd64_inj_attrs ; 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/ * sysfs_attrs ; 
 int /*<<< orphan*/  terminator ; 

__attribute__((used)) static void set_mc_sysfs_attrs(struct mem_ctl_info *mci)
{
	unsigned int i = 0, j = 0;

	for (; i < ARRAY_SIZE(amd64_dbg_attrs); i++)
		sysfs_attrs[i] = amd64_dbg_attrs[i];

	if (boot_cpu_data.x86 >= 0x10)
		for (j = 0; j < ARRAY_SIZE(amd64_inj_attrs); j++, i++)
			sysfs_attrs[i] = amd64_inj_attrs[j];

	sysfs_attrs[i] = terminator;

	mci->mc_driver_sysfs_attributes = sysfs_attrs;
}