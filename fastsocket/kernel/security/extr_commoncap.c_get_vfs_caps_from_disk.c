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
struct dentry {int dummy; } ;
struct cpu_vfs_cap_data {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  memset (struct cpu_vfs_cap_data*,int /*<<< orphan*/ ,int) ; 

int get_vfs_caps_from_disk(const struct dentry *dentry, struct cpu_vfs_cap_data *cpu_caps)
{
	memset(cpu_caps, 0, sizeof(struct cpu_vfs_cap_data));
 	return -ENODATA;
}