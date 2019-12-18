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
struct file_lock {struct file_lock* fl_next; int /*<<< orphan*/  fl_nspid; int /*<<< orphan*/  fl_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  file_lock_list ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_tgid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void locks_insert_lock(struct file_lock **pos, struct file_lock *fl)
{
	list_add(&fl->fl_link, &file_lock_list);

	fl->fl_nspid = get_pid(task_tgid(current));

	/* insert into file's list */
	fl->fl_next = *pos;
	*pos = fl;
}