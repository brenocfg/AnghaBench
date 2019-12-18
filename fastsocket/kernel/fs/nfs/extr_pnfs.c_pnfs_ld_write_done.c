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
struct nfs_write_data {int /*<<< orphan*/  task; struct nfs_pgio_header* header; } ;
struct nfs_pgio_header {TYPE_1__* mds_ops; int /*<<< orphan*/  pnfs_error; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rpc_release ) (struct nfs_write_data*) ;int /*<<< orphan*/  (* rpc_call_done ) (int /*<<< orphan*/ *,struct nfs_write_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pnfs_ld_handle_write_error (struct nfs_write_data*) ; 
 int /*<<< orphan*/  pnfs_set_layoutcommit (struct nfs_write_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct nfs_write_data*) ; 
 int /*<<< orphan*/  stub2 (struct nfs_write_data*) ; 

void pnfs_ld_write_done(struct nfs_write_data *data)
{
	struct nfs_pgio_header *hdr = data->header;

	if (!hdr->pnfs_error) {
		pnfs_set_layoutcommit(data);
		hdr->mds_ops->rpc_call_done(&data->task, data);
	} else
		pnfs_ld_handle_write_error(data);
	hdr->mds_ops->rpc_release(data);
}