#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; } ;
struct TYPE_13__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct nlm_lock {char* caller; TYPE_8__ fl; scalar_t__ svid; TYPE_4__ oh; int /*<<< orphan*/  fh; } ;
struct nlm_args {int /*<<< orphan*/  cookie; struct nlm_lock lock; } ;
struct nlm_rqst {int /*<<< orphan*/  a_owner; struct nlm_args a_args; } ;
struct nfs_fh {int dummy; } ;
struct TYPE_15__ {TYPE_5__* owner; } ;
struct TYPE_16__ {TYPE_6__ nfs_fl; } ;
struct file_lock {int /*<<< orphan*/  fl_type; int /*<<< orphan*/  fl_end; int /*<<< orphan*/  fl_start; TYPE_7__ fl_u; TYPE_3__* fl_file; } ;
struct TYPE_18__ {char* nodename; } ;
struct TYPE_14__ {scalar_t__ pid; } ;
struct TYPE_11__ {TYPE_1__* dentry; } ;
struct TYPE_12__ {TYPE_2__ f_path; } ;
struct TYPE_10__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlmclnt_next_cookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,unsigned int,char*) ; 
 TYPE_9__* utsname () ; 

__attribute__((used)) static void nlmclnt_setlockargs(struct nlm_rqst *req, struct file_lock *fl)
{
	struct nlm_args	*argp = &req->a_args;
	struct nlm_lock	*lock = &argp->lock;

	nlmclnt_next_cookie(&argp->cookie);
	memcpy(&lock->fh, NFS_FH(fl->fl_file->f_path.dentry->d_inode), sizeof(struct nfs_fh));
	lock->caller  = utsname()->nodename;
	lock->oh.data = req->a_owner;
	lock->oh.len  = snprintf(req->a_owner, sizeof(req->a_owner), "%u@%s",
				(unsigned int)fl->fl_u.nfs_fl.owner->pid,
				utsname()->nodename);
	lock->svid = fl->fl_u.nfs_fl.owner->pid;
	lock->fl.fl_start = fl->fl_start;
	lock->fl.fl_end = fl->fl_end;
	lock->fl.fl_type = fl->fl_type;
}