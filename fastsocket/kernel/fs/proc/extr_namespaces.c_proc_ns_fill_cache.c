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
struct task_struct {int dummy; } ;
struct proc_ns_operations {int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int proc_fill_cache (struct file*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,struct proc_ns_operations const*) ; 
 int /*<<< orphan*/  proc_ns_instantiate ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int proc_ns_fill_cache(struct file *filp, void *dirent,
	filldir_t filldir, struct task_struct *task,
	const struct proc_ns_operations *ops)
{
	return proc_fill_cache(filp, dirent, filldir,
				ops->name, strlen(ops->name),
				proc_ns_instantiate, task, ops);
}