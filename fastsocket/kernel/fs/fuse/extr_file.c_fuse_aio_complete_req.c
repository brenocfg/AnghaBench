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
struct TYPE_17__ {int /*<<< orphan*/  error; } ;
struct TYPE_18__ {TYPE_8__ h; TYPE_7__* args; } ;
struct TYPE_13__ {scalar_t__ size; int offset; } ;
struct TYPE_14__ {TYPE_4__ in; } ;
struct TYPE_11__ {scalar_t__ size; } ;
struct TYPE_10__ {scalar_t__ size; int offset; } ;
struct TYPE_12__ {TYPE_2__ out; TYPE_1__ in; } ;
struct TYPE_15__ {TYPE_5__ read; TYPE_3__ write; } ;
struct fuse_req {TYPE_9__ out; TYPE_6__ misc; struct fuse_io_priv* io; } ;
struct fuse_io_priv {int offset; scalar_t__ write; } ;
struct fuse_conn {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_16__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  fuse_aio_complete (struct fuse_io_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_release_user_pages (struct fuse_req*,int) ; 

__attribute__((used)) static void fuse_aio_complete_req(struct fuse_conn *fc, struct fuse_req *req)
{
	struct fuse_io_priv *io = req->io;
	ssize_t pos = -1;

	fuse_release_user_pages(req, !io->write);

	if (io->write) {
		if (req->misc.write.in.size != req->misc.write.out.size)
			pos = req->misc.write.in.offset - io->offset +
				req->misc.write.out.size;
	} else {
		if (req->misc.read.in.size != req->out.args[0].size)
			pos = req->misc.read.in.offset - io->offset +
				req->out.args[0].size;
	}

	fuse_aio_complete(io, req->out.h.error, pos);
}