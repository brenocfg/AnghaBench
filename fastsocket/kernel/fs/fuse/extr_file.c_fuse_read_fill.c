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
struct TYPE_14__ {int argvar; int numargs; TYPE_6__* args; } ;
struct TYPE_10__ {int opcode; int /*<<< orphan*/  nodeid; } ;
struct TYPE_12__ {int numargs; TYPE_4__* args; TYPE_3__ h; } ;
struct fuse_read_in {size_t size; int /*<<< orphan*/  flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  fh; } ;
struct TYPE_8__ {struct fuse_read_in in; } ;
struct TYPE_9__ {TYPE_1__ read; } ;
struct fuse_req {TYPE_7__ out; TYPE_5__ in; TYPE_2__ misc; } ;
struct fuse_file {int /*<<< orphan*/  nodeid; int /*<<< orphan*/  fh; } ;
struct file {int /*<<< orphan*/  f_flags; struct fuse_file* private_data; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_13__ {size_t size; } ;
struct TYPE_11__ {int size; struct fuse_read_in* value; } ;

/* Variables and functions */

void fuse_read_fill(struct fuse_req *req, struct file *file, loff_t pos,
		    size_t count, int opcode)
{
	struct fuse_read_in *inarg = &req->misc.read.in;
	struct fuse_file *ff = file->private_data;

	inarg->fh = ff->fh;
	inarg->offset = pos;
	inarg->size = count;
	inarg->flags = file->f_flags;
	req->in.h.opcode = opcode;
	req->in.h.nodeid = ff->nodeid;
	req->in.numargs = 1;
	req->in.args[0].size = sizeof(struct fuse_read_in);
	req->in.args[0].value = inarg;
	req->out.argvar = 1;
	req->out.numargs = 1;
	req->out.args[0].size = count;
}