#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_13__ {int error; } ;
struct TYPE_14__ {int numargs; TYPE_6__ h; TYPE_5__* args; } ;
struct TYPE_9__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_11__ {int numargs; TYPE_3__* args; TYPE_2__ h; } ;
struct fuse_req {TYPE_7__ out; TYPE_4__ in; } ;
struct fuse_conn {int no_bmap; } ;
struct fuse_bmap_out {int /*<<< orphan*/  block; } ;
struct fuse_bmap_in {int /*<<< orphan*/  blocksize; int /*<<< orphan*/  block; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  outarg ;
typedef  int /*<<< orphan*/  inarg ;
struct TYPE_12__ {int size; struct fuse_bmap_out* value; } ;
struct TYPE_10__ {int size; struct fuse_bmap_in* value; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_blocksize; int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  FUSE_BMAP ; 
 scalar_t__ IS_ERR (struct fuse_req*) ; 
 struct fuse_req* fuse_get_req_nopages (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_put_request (struct fuse_conn*,struct fuse_req*) ; 
 int /*<<< orphan*/  fuse_request_send (struct fuse_conn*,struct fuse_req*) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  get_node_id (struct inode*) ; 
 int /*<<< orphan*/  memset (struct fuse_bmap_in*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static sector_t fuse_bmap(struct address_space *mapping, sector_t block)
{
	struct inode *inode = mapping->host;
	struct fuse_conn *fc = get_fuse_conn(inode);
	struct fuse_req *req;
	struct fuse_bmap_in inarg;
	struct fuse_bmap_out outarg;
	int err;

	if (!inode->i_sb->s_bdev || fc->no_bmap)
		return 0;

	req = fuse_get_req_nopages(fc);
	if (IS_ERR(req))
		return 0;

	memset(&inarg, 0, sizeof(inarg));
	inarg.block = block;
	inarg.blocksize = inode->i_sb->s_blocksize;
	req->in.h.opcode = FUSE_BMAP;
	req->in.h.nodeid = get_node_id(inode);
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(inarg);
	req->in.args[0].value = &inarg;
	req->out.numargs = 1;
	req->out.args[0].size = sizeof(outarg);
	req->out.args[0].value = &outarg;
	fuse_request_send(fc, req);
	err = req->out.h.error;
	fuse_put_request(fc, req);
	if (err == -ENOSYS)
		fc->no_bmap = 1;

	return err ? 0 : outarg.block;
}