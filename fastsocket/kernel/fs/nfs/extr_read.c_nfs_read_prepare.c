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
struct rpc_task {int dummy; } ;
struct TYPE_7__ {TYPE_2__* context; } ;
struct nfs_read_data {TYPE_3__ args; TYPE_1__* header; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* read_rpc_prepare ) (struct rpc_task*,struct nfs_read_data*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  NFS_CONTEXT_BAD ; 
 TYPE_4__* NFS_PROTO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_exit (struct rpc_task*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct rpc_task*,struct nfs_read_data*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void nfs_read_prepare(struct rpc_task *task, void *calldata)
{
	struct nfs_read_data *data = calldata;
	NFS_PROTO(data->header->inode)->read_rpc_prepare(task, data);
	if (unlikely(test_bit(NFS_CONTEXT_BAD, &data->args.context->flags)))
		rpc_exit(task, -EIO);
}