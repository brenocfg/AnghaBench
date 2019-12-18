#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kobject {int /*<<< orphan*/  sd; } ;
struct attribute {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  SYSFS_KOBJ_ATTR ; 
 int sysfs_add_file (int /*<<< orphan*/ ,struct attribute const*,int /*<<< orphan*/ ) ; 

int sysfs_create_file(struct kobject * kobj, const struct attribute * attr)
{
	BUG_ON(!kobj || !kobj->sd || !attr);

	return sysfs_add_file(kobj->sd, attr, SYSFS_KOBJ_ATTR);

}