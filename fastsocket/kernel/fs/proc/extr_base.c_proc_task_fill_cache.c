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
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  filldir_t ;

/* Variables and functions */
 int PROC_NUMBUF ; 
 int proc_fill_cache (struct file*,void*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct task_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_task_instantiate ; 
 int snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int proc_task_fill_cache(struct file *filp, void *dirent, filldir_t filldir,
	struct task_struct *task, int tid)
{
	char name[PROC_NUMBUF];
	int len = snprintf(name, sizeof(name), "%d", tid);
	return proc_fill_cache(filp, dirent, filldir, name, len,
				proc_task_instantiate, task, NULL);
}