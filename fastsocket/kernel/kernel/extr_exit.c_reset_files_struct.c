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
struct task_struct {struct files_struct* files; } ;
struct files_struct {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  put_files_struct (struct files_struct*) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

void reset_files_struct(struct files_struct *files)
{
	struct task_struct *tsk = current;
	struct files_struct *old;

	old = tsk->files;
	task_lock(tsk);
	tsk->files = files;
	task_unlock(tsk);
	put_files_struct(old);
}