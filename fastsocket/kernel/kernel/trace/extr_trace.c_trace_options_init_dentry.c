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
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 struct dentry* tracing_init_dentry () ; 

__attribute__((used)) static struct dentry *trace_options_init_dentry(void)
{
	struct dentry *d_tracer;
	static struct dentry *t_options;

	if (t_options)
		return t_options;

	d_tracer = tracing_init_dentry();
	if (!d_tracer)
		return NULL;

	t_options = debugfs_create_dir("options", d_tracer);
	if (!t_options) {
		pr_warning("Could not create debugfs directory 'options'\n");
		return NULL;
	}

	return t_options;
}