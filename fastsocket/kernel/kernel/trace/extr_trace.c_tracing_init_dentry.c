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
 struct dentry* d_tracer ; 
 struct dentry* debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_initialized () ; 
 int /*<<< orphan*/  pr_warning (char*) ; 

struct dentry *tracing_init_dentry(void)
{
	static int once;

	if (d_tracer)
		return d_tracer;

	if (!debugfs_initialized())
		return NULL;

	d_tracer = debugfs_create_dir("tracing", NULL);

	if (!d_tracer && !once) {
		once = 1;
		pr_warning("Could not create debugfs directory 'tracing'\n");
		return NULL;
	}

	return d_tracer;
}