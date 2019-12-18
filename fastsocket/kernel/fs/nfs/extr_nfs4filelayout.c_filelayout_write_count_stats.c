#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rpc_task {int dummy; } ;
struct nfs_write_data {TYPE_2__* header; } ;
struct TYPE_6__ {TYPE_1__* client; } ;
struct TYPE_5__ {int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  cl_metrics; } ;

/* Variables and functions */
 TYPE_3__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_count_iostats (struct rpc_task*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filelayout_write_count_stats(struct rpc_task *task, void *data)
{
	struct nfs_write_data *wdata = (struct nfs_write_data *)data;

	rpc_count_iostats(task, NFS_SERVER(wdata->header->inode)->client->cl_metrics);
}