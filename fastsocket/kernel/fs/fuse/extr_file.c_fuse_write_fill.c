#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct fuse_write_out {int dummy; } ;
struct fuse_write_in {size_t size; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
struct TYPE_16__ {int numargs; TYPE_7__* args; } ;
struct TYPE_11__ {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  opcode; } ;
struct TYPE_14__ {int numargs; TYPE_5__* args; TYPE_3__ h; } ;
struct TYPE_9__ {struct fuse_write_out out; struct fuse_write_in in; } ;
struct TYPE_10__ {TYPE_1__ write; } ;
struct fuse_req {TYPE_8__ out; TYPE_6__ in; TYPE_2__ misc; } ;
struct fuse_file {TYPE_4__* fc; int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_15__ {int size; struct fuse_write_out* value; } ;
struct TYPE_13__ {int size; struct fuse_write_in* value; } ;
struct TYPE_12__ {int minor; } ;

/* Variables and functions */
 int FUSE_COMPAT_WRITE_IN_SIZE ; 
 int /*<<< orphan*/  FUSE_WRITE ; 

__attribute__((used)) static void fuse_write_fill(struct fuse_req *req, struct fuse_file *ff,
			    loff_t pos, size_t count)
{
	struct fuse_write_in *inarg = &req->misc.write.in;
	struct fuse_write_out *outarg = &req->misc.write.out;

	inarg->fh = ff->fh;
	inarg->offset = pos;
	inarg->size = count;
	req->in.h.opcode = FUSE_WRITE;
	req->in.h.nodeid = ff->nodeid;
	req->in.numargs = 2;
	if (ff->fc->minor < 9)
		req->in.args[0].size = FUSE_COMPAT_WRITE_IN_SIZE;
	else
		req->in.args[0].size = sizeof(struct fuse_write_in);
	req->in.args[0].value = inarg;
	req->in.args[1].size = count;
	req->out.numargs = 1;
	req->out.args[0].size = sizeof(struct fuse_write_out);
	req->out.args[0].value = outarg;
}