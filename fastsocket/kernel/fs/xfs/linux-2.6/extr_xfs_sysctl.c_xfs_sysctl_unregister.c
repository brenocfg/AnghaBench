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
 int /*<<< orphan*/  unregister_sysctl_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_table_header ; 

void
xfs_sysctl_unregister(void)
{
	unregister_sysctl_table(xfs_table_header);
}