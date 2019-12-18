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
struct nfs_read_data {int /*<<< orphan*/  task; struct nfs_pgio_header* header; } ;
struct nfs_pgio_header {TYPE_1__* mds_ops; int /*<<< orphan*/  pnfs_error; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpc_release ) (struct nfs_read_data*) ;int /*<<< orphan*/  (* rpc_call_done ) (int /*<<< orphan*/ *,struct nfs_read_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __nfs4_read_done_cb (struct nfs_read_data*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  pnfs_ld_handle_read_error (struct nfs_read_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct nfs_read_data*) ; 
 int /*<<< orphan*/  stub2 (struct nfs_read_data*) ; 

void pnfs_ld_read_done(struct nfs_read_data *data)
{
	struct nfs_pgio_header *hdr = data->header;

	if (likely(!hdr->pnfs_error)) {
		__nfs4_read_done_cb(data);
		hdr->mds_ops->rpc_call_done(&data->task, data);
	} else
		pnfs_ld_handle_read_error(data);
	hdr->mds_ops->rpc_release(data);
}