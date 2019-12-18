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
struct nfs_pageio_descriptor {int /*<<< orphan*/  pg_inode; int /*<<< orphan*/  pg_bsize; int /*<<< orphan*/ * pg_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  wsize; } ;

/* Variables and functions */
 TYPE_1__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_write_ops ; 

void nfs_pageio_reset_write_mds(struct nfs_pageio_descriptor *pgio)
{
	pgio->pg_ops = &nfs_pageio_write_ops;
	pgio->pg_bsize = NFS_SERVER(pgio->pg_inode)->wsize;
}