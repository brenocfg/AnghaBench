#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int /*<<< orphan*/  tk_status; } ;
struct TYPE_4__ {scalar_t__ offset; scalar_t__ count; } ;
struct TYPE_3__ {scalar_t__ count; scalar_t__ eof; } ;
struct nfs_read_data {TYPE_2__ args; TYPE_1__ res; struct nfs_pgio_header* header; } ;
struct nfs_pgio_header {scalar_t__ io_start; scalar_t__ good_bytes; int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_IOHDR_EOF ; 
 int /*<<< orphan*/  NFS_IOHDR_ERROR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_readpage_result (struct rpc_task*,struct nfs_read_data*) ; 
 int /*<<< orphan*/  nfs_readpage_retry (struct rpc_task*,struct nfs_read_data*) ; 
 int /*<<< orphan*/  nfs_set_pgio_error (struct nfs_pgio_header*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfs_readpage_result_common(struct rpc_task *task, void *calldata)
{
	struct nfs_read_data *data = calldata;
	struct nfs_pgio_header *hdr = data->header;

	/* Note the only returns of nfs_readpage_result are 0 and -EAGAIN */
	if (nfs_readpage_result(task, data) != 0)
		return;
	if (task->tk_status < 0)
		nfs_set_pgio_error(hdr, task->tk_status, data->args.offset);
	else if (data->res.eof) {
		loff_t bound;

		bound = data->args.offset + data->res.count;
		spin_lock(&hdr->lock);
		if (bound < hdr->io_start + hdr->good_bytes) {
			set_bit(NFS_IOHDR_EOF, &hdr->flags);
			clear_bit(NFS_IOHDR_ERROR, &hdr->flags);
			hdr->good_bytes = bound - hdr->io_start;
		}
		spin_unlock(&hdr->lock);
	} else if (data->res.count != data->args.count)
		nfs_readpage_retry(task, data);
}