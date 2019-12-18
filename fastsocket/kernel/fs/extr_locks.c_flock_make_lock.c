#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct file_lock {int fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_flags; int /*<<< orphan*/  fl_pid; struct file* fl_file; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tgid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FL_FLOCK ; 
 int /*<<< orphan*/  OFFSET_MAX ; 
 TYPE_1__* current ; 
 int flock_translate_cmd (unsigned int) ; 
 struct file_lock* locks_alloc_lock () ; 

__attribute__((used)) static int flock_make_lock(struct file *filp, struct file_lock **lock,
		unsigned int cmd)
{
	struct file_lock *fl;
	int type = flock_translate_cmd(cmd);
	if (type < 0)
		return type;
	
	fl = locks_alloc_lock();
	if (fl == NULL)
		return -ENOMEM;

	fl->fl_file = filp;
	fl->fl_pid = current->tgid;
	fl->fl_flags = FL_FLOCK;
	fl->fl_type = type;
	fl->fl_end = OFFSET_MAX;
	
	*lock = fl;
	return 0;
}