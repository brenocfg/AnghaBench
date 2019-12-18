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
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnic_trace_debugfs_file ; 
 int /*<<< orphan*/ * fnic_trace_debugfs_root ; 
 int /*<<< orphan*/ * fnic_trace_enable ; 

void fnic_trace_debugfs_terminate(void)
{
	if (fnic_trace_debugfs_file) {
		debugfs_remove(fnic_trace_debugfs_file);
		fnic_trace_debugfs_file = NULL;
	}
	if (fnic_trace_enable) {
		debugfs_remove(fnic_trace_enable);
		fnic_trace_enable = NULL;
	}
	if (fnic_trace_debugfs_root) {
		debugfs_remove(fnic_trace_debugfs_root);
		fnic_trace_debugfs_root = NULL;
	}
}