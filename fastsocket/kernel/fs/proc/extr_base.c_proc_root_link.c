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
struct path {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int get_fs_path (struct task_struct*,struct path*,int) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 

__attribute__((used)) static int proc_root_link(struct inode *inode, struct path *path)
{
	struct task_struct *task = get_proc_task(inode);
	int result = -ENOENT;

	if (task) {
		result = get_fs_path(task, path, 1);
		put_task_struct(task);
	}
	return result;
}