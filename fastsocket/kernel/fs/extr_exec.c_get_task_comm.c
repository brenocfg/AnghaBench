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
struct task_struct {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

char *get_task_comm(char *buf, struct task_struct *tsk)
{
	/* buf must be at least sizeof(tsk->comm) in size */
	task_lock(tsk);
	strncpy(buf, tsk->comm, sizeof(tsk->comm));
	task_unlock(tsk);
	return buf;
}