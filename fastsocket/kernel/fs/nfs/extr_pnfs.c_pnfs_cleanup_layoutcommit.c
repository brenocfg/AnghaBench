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
struct nfs_server {TYPE_2__* pnfs_curr_ld; } ;
struct TYPE_3__ {int /*<<< orphan*/  inode; } ;
struct nfs4_layoutcommit_data {TYPE_1__ args; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* cleanup_layoutcommit ) (struct nfs4_layoutcommit_data*) ;} ;

/* Variables and functions */
 struct nfs_server* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct nfs4_layoutcommit_data*) ; 

void pnfs_cleanup_layoutcommit(struct nfs4_layoutcommit_data *data)
{
	struct nfs_server *nfss = NFS_SERVER(data->args.inode);

	if (nfss->pnfs_curr_ld->cleanup_layoutcommit)
		nfss->pnfs_curr_ld->cleanup_layoutcommit(data);
}