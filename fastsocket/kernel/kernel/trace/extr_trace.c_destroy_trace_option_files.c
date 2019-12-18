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
struct trace_option_dentry {scalar_t__ entry; scalar_t__ opt; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct trace_option_dentry*) ; 

__attribute__((used)) static void
destroy_trace_option_files(struct trace_option_dentry *topts)
{
	int cnt;

	if (!topts)
		return;

	for (cnt = 0; topts[cnt].opt; cnt++) {
		if (topts[cnt].entry)
			debugfs_remove(topts[cnt].entry);
	}

	kfree(topts);
}