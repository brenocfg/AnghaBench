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
struct file_lock {int /*<<< orphan*/  fl_lmops; int /*<<< orphan*/  fl_ops; int /*<<< orphan*/  fl_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  __locks_copy_lock (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  locks_copy_private (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  locks_release_private (struct file_lock*) ; 

void locks_copy_lock(struct file_lock *new, struct file_lock *fl)
{
	locks_release_private(new);

	__locks_copy_lock(new, fl);
	new->fl_file = fl->fl_file;
	new->fl_ops = fl->fl_ops;
	new->fl_lmops = fl->fl_lmops;

	locks_copy_private(new, fl);
}