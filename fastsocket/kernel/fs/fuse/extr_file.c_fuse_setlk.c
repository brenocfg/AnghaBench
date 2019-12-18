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
struct inode {int dummy; } ;
struct TYPE_10__ {int error; } ;
struct TYPE_11__ {TYPE_4__ h; } ;
struct fuse_req {TYPE_5__ out; } ;
struct fuse_conn {int dummy; } ;
struct file_lock {int fl_flags; scalar_t__ fl_type; TYPE_3__* fl_lmops; } ;
struct TYPE_8__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_12__ {int /*<<< orphan*/  tgid; } ;
struct TYPE_9__ {scalar_t__ fl_grant; } ;
struct TYPE_7__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOLCK ; 
 int ERESTARTSYS ; 
 int FL_CLOSE ; 
 int FL_SLEEP ; 
 int FUSE_SETLK ; 
 int FUSE_SETLKW ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 TYPE_6__* current ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_lk_fill (struct fuse_req*,struct file*,struct file_lock*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 

__attribute__((used)) static int fuse_setlk(struct file *file, struct file_lock *fl, int flock)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	int opcode = (fl->fl_flags & FL_SLEEP) ? FUSE_SETLKW : FUSE_SETLK;
	pid_t pid = fl->fl_type != F_UNLCK ? current->tgid : 0;
	int err;

	if (fl->fl_lmops && fl->fl_lmops->fl_grant) {
		/* NLM needs asynchronous locks, which we don't support yet */
		return -ENOLCK;
	}

	/* Unlock on close is handled by the flush method */
	if (fl->fl_flags & FL_CLOSE)
		return 0;

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return PTR_ERR(req);

	fuse_lk_fill(req, file, fl, opcode, pid, flock);
	fuse_request_send(fc, req);
	err = req->out.h.error;
	/* locking is restartable */
	if (err == -EINTR)
		err = -ERESTARTSYS;
	fuse_put_request(fc, req);
	return err;
}