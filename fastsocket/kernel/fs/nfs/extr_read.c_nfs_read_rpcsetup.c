#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int count; scalar_t__ eof; int /*<<< orphan*/ * fattr; } ;
struct TYPE_7__ {unsigned int count; int /*<<< orphan*/  lock_context; int /*<<< orphan*/  context; int /*<<< orphan*/  pages; scalar_t__ pgbase; scalar_t__ offset; int /*<<< orphan*/  fh; } ;
struct TYPE_6__ {int /*<<< orphan*/  pagevec; } ;
struct nfs_read_data {int /*<<< orphan*/  fattr; TYPE_4__ res; TYPE_3__ args; TYPE_2__ pages; TYPE_1__* header; } ;
struct nfs_page {int /*<<< orphan*/  wb_lock_context; int /*<<< orphan*/  wb_context; scalar_t__ wb_pgbase; } ;
struct TYPE_5__ {int /*<<< orphan*/  inode; struct nfs_page* req; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 

__attribute__((used)) static void nfs_read_rpcsetup(struct nfs_read_data *data,
		unsigned int count, unsigned int offset)
{
	struct nfs_page *req = data->header->req;

	data->args.fh     = NFS_FH(data->header->inode);
	data->args.offset = req_offset(req) + offset;
	data->args.pgbase = req->wb_pgbase + offset;
	data->args.pages  = data->pages.pagevec;
	data->args.count  = count;
	data->args.context = get_nfs_open_context(req->wb_context);
	data->args.lock_context = req->wb_lock_context;

	data->res.fattr   = &data->fattr;
	data->res.count   = count;
	data->res.eof     = 0;
	nfs_fattr_init(&data->fattr);
}