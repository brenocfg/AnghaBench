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
struct file_lock {int /*<<< orphan*/ * fl_lmops; int /*<<< orphan*/ * fl_ops; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_flags; int /*<<< orphan*/ * fl_file; int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_owner; } ;

/* Variables and functions */

void __locks_copy_lock(struct file_lock *new, const struct file_lock *fl)
{
	new->fl_owner = fl->fl_owner;
	new->fl_pid = fl->fl_pid;
	new->fl_file = NULL;
	new->fl_flags = fl->fl_flags;
	new->fl_type = fl->fl_type;
	new->fl_start = fl->fl_start;
	new->fl_end = fl->fl_end;
	new->fl_ops = NULL;
	new->fl_lmops = NULL;
}