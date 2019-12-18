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
struct rpc_task {int dummy; } ;
struct nfs_write_data {TYPE_2__* header; } ;
struct TYPE_4__ {TYPE_1__* mds_ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rpc_call_done ) (struct rpc_task*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rpc_task*,void*) ; 

__attribute__((used)) static void filelayout_write_call_done(struct rpc_task *task, void *data)
{
	struct nfs_write_data *wdata = data;

	/* Note this may cause RPC to be resent */
	wdata->header->mds_ops->rpc_call_done(task, data);
}