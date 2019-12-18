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
struct fuse_file_lock {int type; int /*<<< orphan*/  pid; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct file_lock {int fl_type; int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; } ;

/* Variables and functions */
 int EIO ; 
#define  F_RDLCK 130 
#define  F_UNLCK 129 
#define  F_WRLCK 128 
 int /*<<< orphan*/  OFFSET_MAX ; 

__attribute__((used)) static int convert_fuse_file_lock(const struct fuse_file_lock *ffl,
				  struct file_lock *fl)
{
	switch (ffl->type) {
	case F_UNLCK:
		break;

	case F_RDLCK:
	case F_WRLCK:
		if (ffl->start > OFFSET_MAX || ffl->end > OFFSET_MAX ||
		    ffl->end < ffl->start)
			return -EIO;

		fl->fl_start = ffl->start;
		fl->fl_end = ffl->end;
		fl->fl_pid = ffl->pid;
		break;

	default:
		return -EIO;
	}
	fl->fl_type = ffl->type;
	return 0;
}