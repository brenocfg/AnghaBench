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
struct pid_entry {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_base_instantiate ; 
 int proc_fill_cache (struct file*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,struct pid_entry const*) ; 

__attribute__((used)) static int proc_base_fill_cache(struct file *filp, void *dirent,
	filldir_t filldir, struct task_struct *task, const struct pid_entry *p)
{
	return proc_fill_cache(filp, dirent, filldir, p->name, p->len,
				proc_base_instantiate, task, p);
}