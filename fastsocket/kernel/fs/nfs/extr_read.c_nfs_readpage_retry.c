#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct nfs_readres {scalar_t__ count; } ;
struct nfs_readargs {int /*<<< orphan*/  count; int /*<<< orphan*/  pgbase; int /*<<< orphan*/  offset; } ;
struct nfs_read_data {int /*<<< orphan*/  mds_offset; TYPE_1__* header; struct nfs_readres res; struct nfs_readargs args; } ;
struct TYPE_2__ {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  NFSIOS_SHORTREAD ; 
 int /*<<< orphan*/  nfs_inc_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_set_pgio_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_restart_call_prepare (struct rpc_task*) ; 

__attribute__((used)) static void nfs_readpage_retry(struct rpc_task *task, struct nfs_read_data *data)
{
	struct nfs_readargs *argp = &data->args;
	struct nfs_readres *resp = &data->res;

	/* This is a short read! */
	nfs_inc_stats(data->header->inode, NFSIOS_SHORTREAD);
	/* Has the server at least made some progress? */
	if (resp->count == 0) {
		nfs_set_pgio_error(data->header, -EIO, argp->offset);
		return;
	}
	/* Yes, so retry the read at the end of the data */
	data->mds_offset += resp->count;
	argp->offset += resp->count;
	argp->pgbase += resp->count;
	argp->count -= resp->count;
	rpc_restart_call_prepare(task);
}