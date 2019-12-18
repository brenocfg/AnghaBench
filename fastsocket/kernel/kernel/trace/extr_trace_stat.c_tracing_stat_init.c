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

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 int /*<<< orphan*/  stat_dir ; 
 struct dentry* tracing_init_dentry () ; 

__attribute__((used)) static int tracing_stat_init(void)
{
	struct dentry *d_tracing;

	d_tracing = tracing_init_dentry();

	stat_dir = debugfs_create_dir("trace_stat", d_tracing);
	if (!stat_dir)
		pr_warning("Could not create debugfs "
			   "'trace_stat' entry\n");
	return 0;
}