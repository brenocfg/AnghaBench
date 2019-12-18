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
 int /*<<< orphan*/  atalk_path ; 
 int /*<<< orphan*/  atalk_table ; 
 int /*<<< orphan*/  atalk_table_header ; 
 int /*<<< orphan*/  register_sysctl_paths (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void atalk_register_sysctl(void)
{
	atalk_table_header = register_sysctl_paths(atalk_path, atalk_table);
}