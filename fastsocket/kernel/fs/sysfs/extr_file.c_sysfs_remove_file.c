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
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_hash_and_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sysfs_remove_file(struct kobject * kobj, const struct attribute * attr)
{
	sysfs_hash_and_remove(kobj->sd, attr->name);
}