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
struct TYPE_2__ {int /*<<< orphan*/  value; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_parent ; 
 int /*<<< orphan*/  fops_pid_param ; 
 TYPE_1__* pid_files ; 

__attribute__((used)) static void intel_pstate_debug_expose_params(void)
{
	int i = 0;

	debugfs_parent = debugfs_create_dir("pstate_snb", NULL);
	if (IS_ERR_OR_NULL(debugfs_parent))
		return;
	while (pid_files[i].name) {
		debugfs_create_file(pid_files[i].name, 0660,
				debugfs_parent, pid_files[i].value,
				&fops_pid_param);
		i++;
	}
}