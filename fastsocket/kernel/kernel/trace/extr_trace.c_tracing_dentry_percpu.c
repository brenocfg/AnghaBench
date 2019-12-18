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
 struct dentry* d_percpu ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  pr_warning (char*) ; 
 struct dentry* tracing_init_dentry () ; 

struct dentry *tracing_dentry_percpu(void)
{
	static int once;
	struct dentry *d_tracer;

	if (d_percpu)
		return d_percpu;

	d_tracer = tracing_init_dentry();

	if (!d_tracer)
		return NULL;

	d_percpu = debugfs_create_dir("per_cpu", d_tracer);

	if (!d_percpu && !once) {
		once = 1;
		pr_warning("Could not create debugfs directory 'per_cpu'\n");
		return NULL;
	}

	return d_percpu;
}