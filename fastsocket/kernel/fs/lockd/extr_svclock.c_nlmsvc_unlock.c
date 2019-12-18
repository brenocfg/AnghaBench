#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  fl_type; scalar_t__ fl_end; scalar_t__ fl_start; int /*<<< orphan*/  fl_pid; } ;
struct nlm_lock {TYPE_6__ fl; } ;
struct nlm_file {TYPE_5__* f_file; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_9__ {TYPE_2__* dentry; } ;
struct TYPE_11__ {TYPE_3__ f_path; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_id; } ;
struct TYPE_8__ {TYPE_1__* d_inode; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_ino; TYPE_4__* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,long long) ; 
 int /*<<< orphan*/  nlm_granted ; 
 int /*<<< orphan*/  nlm_lck_denied_nolocks ; 
 int /*<<< orphan*/  nlmsvc_cancel_blocked (struct nlm_file*,struct nlm_lock*) ; 
 int vfs_lock_file (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ *) ; 

__be32
nlmsvc_unlock(struct nlm_file *file, struct nlm_lock *lock)
{
	int	error;

	dprintk("lockd: nlmsvc_unlock(%s/%ld, pi=%d, %Ld-%Ld)\n",
				file->f_file->f_path.dentry->d_inode->i_sb->s_id,
				file->f_file->f_path.dentry->d_inode->i_ino,
				lock->fl.fl_pid,
				(long long)lock->fl.fl_start,
				(long long)lock->fl.fl_end);

	/* First, cancel any lock that might be there */
	nlmsvc_cancel_blocked(file, lock);

	lock->fl.fl_type = F_UNLCK;
	error = vfs_lock_file(file->f_file, F_SETLK, &lock->fl, NULL);

	return (error < 0)? nlm_lck_denied_nolocks : nlm_granted;
}