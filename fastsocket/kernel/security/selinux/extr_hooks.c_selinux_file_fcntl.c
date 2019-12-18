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
struct TYPE_3__ {TYPE_2__* dentry; } ;
struct file {unsigned long f_flags; TYPE_1__ f_path; } ;
struct cred {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FILE__LOCK ; 
 int /*<<< orphan*/  FILE__WRITE ; 
#define  F_GETFL 139 
#define  F_GETLK 138 
#define  F_GETLK64 137 
#define  F_GETOWN 136 
#define  F_GETSIG 135 
#define  F_SETFL 134 
#define  F_SETLK 133 
#define  F_SETLK64 132 
#define  F_SETLKW 131 
#define  F_SETLKW64 130 
#define  F_SETOWN 129 
#define  F_SETSIG 128 
 unsigned long O_APPEND ; 
 struct cred* current_cred () ; 
 int file_has_perm (struct cred const*,struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_file_fcntl(struct file *file, unsigned int cmd,
			      unsigned long arg)
{
	const struct cred *cred = current_cred();
	int err = 0;

	switch (cmd) {
	case F_SETFL:
		if (!file->f_path.dentry || !file->f_path.dentry->d_inode) {
			err = -EINVAL;
			break;
		}

		if ((file->f_flags & O_APPEND) && !(arg & O_APPEND)) {
			err = file_has_perm(cred, file, FILE__WRITE);
			break;
		}
		/* fall through */
	case F_SETOWN:
	case F_SETSIG:
	case F_GETFL:
	case F_GETOWN:
	case F_GETSIG:
		/* Just check FD__USE permission */
		err = file_has_perm(cred, file, 0);
		break;
	case F_GETLK:
	case F_SETLK:
	case F_SETLKW:
#if BITS_PER_LONG == 32
	case F_GETLK64:
	case F_SETLK64:
	case F_SETLKW64:
#endif
		if (!file->f_path.dentry || !file->f_path.dentry->d_inode) {
			err = -EINVAL;
			break;
		}
		err = file_has_perm(cred, file, FILE__LOCK);
		break;
	}

	return err;
}