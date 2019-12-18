#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_10__ {int numargs; TYPE_4__ h; TYPE_3__* args; } ;
struct fuse_req {TYPE_5__ out; } ;
struct fuse_lk_out {int /*<<< orphan*/  lk; } ;
struct fuse_conn {int dummy; } ;
struct file_lock {int dummy; } ;
struct TYPE_7__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
typedef  int /*<<< orphan*/  outarg ;
struct TYPE_8__ {int size; struct fuse_lk_out* value; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUSE_GETLK ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 int convert_fuse_file_lock (int /*<<< orphan*/ *,struct file_lock*) ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_lk_fill (struct fuse_req*,struct file*,struct file_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 

__attribute__((used)) static int fuse_getlk(struct file *file, struct file_lock *fl)
{
	struct inode *inode = file->f_path.dentry->d_inode;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	struct fuse_lk_out outarg;
	int err;

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return PTR_ERR(req);

	fuse_lk_fill(req, file, fl, FUSE_GETLK, 0, 0);
	req->out.numargs = 1;
	req->out.args[0].size = sizeof(outarg);
	req->out.args[0].value = &outarg;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (!err)
		err = convert_fuse_file_lock(&outarg.lk, fl);

	return err;
}