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
struct super_block {int dummy; } ;
struct kstatfs {int /*<<< orphan*/  f_type; } ;
struct fuse_statfs_out {int /*<<< orphan*/  st; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_10__ {int numargs; TYPE_4__ h; TYPE_3__* args; } ;
struct TYPE_6__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_7__ {TYPE_1__ h; scalar_t__ numargs; } ;
struct fuse_req {TYPE_5__ out; TYPE_2__ in; } ;
struct fuse_conn {int minor; } ;
struct dentry {int /*<<< orphan*/  d_inode; struct super_block* d_sb; } ;
typedef  int /*<<< orphan*/  outarg ;
struct TYPE_8__ {int size; struct fuse_statfs_out* value; } ;

/* Variables and functions */
 int FUSE_COMPAT_STATFS_SIZE ; 
 int /*<<< orphan*/  FUSE_STATFS ; 
 int /*<<< orphan*/  FUSE_SUPER_MAGIC ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 int PTR_ERR (struct fuse_req*) ; 
 int /*<<< orphan*/  convert_fuse_statfs (struct kstatfs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fuse_allow_current_process (struct fuse_conn*) ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_conn* get_fuse_conn_super (struct super_block*) ; 
 int /*<<< orphan*/  get_node_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fuse_statfs_out*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int fuse_statfs(struct dentry *dentry, struct kstatfs *buf)
{
	struct super_block *sb = dentry->d_sb;
	struct fuse_conn *fc = get_fuse_conn_super(sb);
	struct fuse_req *req;
	struct fuse_statfs_out outarg;
	int err;

	if (!fuse_allow_current_process(fc)) {
		buf->f_type = FUSE_SUPER_MAGIC;
		return 0;
	}

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return PTR_ERR(req);

	memset(&outarg, 0, sizeof(outarg));
	req->in.numargs = 0;
	req->in.h.opcode = FUSE_STATFS;
	req->in.h.nodeid = get_node_id(dentry->d_inode);
	req->out.numargs = 1;
	req->out.args[0].size =
		fc->minor < 4 ? FUSE_COMPAT_STATFS_SIZE : sizeof(outarg);
	req->out.args[0].value = &outarg;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	if (!err)
		convert_fuse_statfs(buf, &outarg.st);
	fuse_put_request(fc, req);
	return err;
}