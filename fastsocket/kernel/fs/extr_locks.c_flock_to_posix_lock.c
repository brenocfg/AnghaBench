#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct flock {int l_whence; scalar_t__ l_start; scalar_t__ l_len; int /*<<< orphan*/  l_type; } ;
struct file_lock {scalar_t__ fl_end; scalar_t__ fl_start; int /*<<< orphan*/ * fl_lmops; int /*<<< orphan*/ * fl_ops; int /*<<< orphan*/  fl_flags; struct file* fl_file; int /*<<< orphan*/  fl_pid; int /*<<< orphan*/  fl_owner; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {scalar_t__ f_pos; TYPE_2__ f_path; } ;
typedef  scalar_t__ off_t ;
struct TYPE_6__ {int /*<<< orphan*/  tgid; int /*<<< orphan*/  files; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  FL_POSIX ; 
 scalar_t__ OFFSET_MAX ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int assign_type (struct file_lock*,int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 
 scalar_t__ i_size_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flock_to_posix_lock(struct file *filp, struct file_lock *fl,
			       struct flock *l)
{
	off_t start, end;

	switch (l->l_whence) {
	case SEEK_SET:
		start = 0;
		break;
	case SEEK_CUR:
		start = filp->f_pos;
		break;
	case SEEK_END:
		start = i_size_read(filp->f_path.dentry->d_inode);
		break;
	default:
		return -EINVAL;
	}

	/* POSIX-1996 leaves the case l->l_len < 0 undefined;
	   POSIX-2001 defines it. */
	start += l->l_start;
	if (start < 0)
		return -EINVAL;
	fl->fl_end = OFFSET_MAX;
	if (l->l_len > 0) {
		end = start + l->l_len - 1;
		fl->fl_end = end;
	} else if (l->l_len < 0) {
		end = start - 1;
		fl->fl_end = end;
		start += l->l_len;
		if (start < 0)
			return -EINVAL;
	}
	fl->fl_start = start;	/* we record the absolute position */
	if (fl->fl_end < fl->fl_start)
		return -EOVERFLOW;
	
	fl->fl_owner = current->files;
	fl->fl_pid = current->tgid;
	fl->fl_file = filp;
	fl->fl_flags = FL_POSIX;
	fl->fl_ops = NULL;
	fl->fl_lmops = NULL;

	return assign_type(fl, l->l_type);
}