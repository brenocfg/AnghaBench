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
struct TYPE_8__ {unsigned int count; int /*<<< orphan*/ * verf; int /*<<< orphan*/ * fattr; } ;
struct TYPE_7__ {unsigned int count; int /*<<< orphan*/  stable; int /*<<< orphan*/  lock_context; int /*<<< orphan*/  context; int /*<<< orphan*/  pages; scalar_t__ pgbase; scalar_t__ offset; int /*<<< orphan*/  fh; } ;
struct TYPE_6__ {int /*<<< orphan*/  pagevec; } ;
struct nfs_write_data {int /*<<< orphan*/  fattr; int /*<<< orphan*/  verf; TYPE_4__ res; TYPE_3__ args; TYPE_2__ pages; scalar_t__ mds_offset; TYPE_1__* header; } ;
struct nfs_page {int /*<<< orphan*/  wb_lock_context; int /*<<< orphan*/  wb_context; scalar_t__ wb_pgbase; } ;
struct nfs_commit_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  inode; struct nfs_page* req; } ;

/* Variables and functions */
#define  FLUSH_COND_STABLE 128 
 int FLUSH_STABLE ; 
 int /*<<< orphan*/  NFS_FH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_FILE_SYNC ; 
 int /*<<< orphan*/  NFS_UNSTABLE ; 
 int /*<<< orphan*/  get_nfs_open_context (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_reqs_to_commit (struct nfs_commit_info*) ; 
 scalar_t__ req_offset (struct nfs_page*) ; 

__attribute__((used)) static void nfs_write_rpcsetup(struct nfs_write_data *data,
		unsigned int count, unsigned int offset,
		int how, struct nfs_commit_info *cinfo)
{
	struct nfs_page *req = data->header->req;

	/* Set up the RPC argument and reply structs
	 * NB: take care not to mess about with data->commit et al. */

	data->args.fh     = NFS_FH(data->header->inode);
	data->args.offset = req_offset(req) + offset;
	/* pnfs_set_layoutcommit needs this */
	data->mds_offset = data->args.offset;
	data->args.pgbase = req->wb_pgbase + offset;
	data->args.pages  = data->pages.pagevec;
	data->args.count  = count;
	data->args.context = get_nfs_open_context(req->wb_context);
	data->args.lock_context = req->wb_lock_context;
	data->args.stable  = NFS_UNSTABLE;
	switch (how & (FLUSH_STABLE | FLUSH_COND_STABLE)) {
	case 0:
		break;
	case FLUSH_COND_STABLE:
		if (nfs_reqs_to_commit(cinfo))
			break;
	default:
		data->args.stable = NFS_FILE_SYNC;
	}

	data->res.fattr   = &data->fattr;
	data->res.count   = count;
	data->res.verf    = &data->verf;
	nfs_fattr_init(&data->fattr);
}