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
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,void*,struct file_operations const*) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 

struct dentry *trace_create_file(const char *name,
				 mode_t mode,
				 struct dentry *parent,
				 void *data,
				 const struct file_operations *fops)
{
	struct dentry *ret;

	ret = debugfs_create_file(name, mode, parent, data, fops);
	if (!ret)
		pr_warning("Could not create debugfs '%s' entry\n", name);

	return ret;
}