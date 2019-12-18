#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file_lock {TYPE_2__* fl_lmops; TYPE_1__* fl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* fl_copy_lock ) (struct file_lock*,struct file_lock*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* fl_copy_lock ) (struct file_lock*,struct file_lock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct file_lock*,struct file_lock*) ; 
 int /*<<< orphan*/  stub2 (struct file_lock*,struct file_lock*) ; 

__attribute__((used)) static void locks_copy_private(struct file_lock *new, struct file_lock *fl)
{
	if (fl->fl_ops) {
		if (fl->fl_ops->fl_copy_lock)
			fl->fl_ops->fl_copy_lock(new, fl);
		new->fl_ops = fl->fl_ops;
	}
	if (fl->fl_lmops) {
		if (fl->fl_lmops->fl_copy_lock)
			fl->fl_lmops->fl_copy_lock(new, fl);
		new->fl_lmops = fl->fl_lmops;
	}
}