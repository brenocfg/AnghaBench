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
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int /*<<< orphan*/  dbfs_file_2fc ; 
 int /*<<< orphan*/  hypfs_dbfs_remove_file (int /*<<< orphan*/ *) ; 

void hypfs_vm_exit(void)
{
	if (!MACHINE_IS_VM)
		return;
	hypfs_dbfs_remove_file(&dbfs_file_2fc);
}