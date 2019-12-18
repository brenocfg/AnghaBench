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
 int /*<<< orphan*/  fs_table ; 
 scalar_t__ fs_table_header ; 
 scalar_t__ register_sysctl_table (int /*<<< orphan*/ ) ; 

void coda_sysctl_init(void)
{
#ifdef CONFIG_SYSCTL
	if ( !fs_table_header )
		fs_table_header = register_sysctl_table(fs_table);
#endif
}