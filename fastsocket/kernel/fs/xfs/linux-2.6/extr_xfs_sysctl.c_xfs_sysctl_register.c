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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  register_sysctl_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_root_table ; 
 int /*<<< orphan*/  xfs_table_header ; 

int
xfs_sysctl_register(void)
{
	xfs_table_header = register_sysctl_table(xfs_root_table);
	if (!xfs_table_header)
		return -ENOMEM;
	return 0;
}