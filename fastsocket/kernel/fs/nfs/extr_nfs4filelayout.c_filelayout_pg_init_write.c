#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_dreq; int /*<<< orphan*/  pg_inode; } ;
struct nfs_page {scalar_t__ wb_offset; scalar_t__ wb_pgbase; int /*<<< orphan*/  wb_context; } ;
struct nfs_commit_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  IOMODE_RW ; 
 int /*<<< orphan*/  NFS4_MAX_UINT64 ; 
 int filelayout_alloc_commit_info (int /*<<< orphan*/ *,struct nfs_commit_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_init_cinfo (struct nfs_commit_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_pageio_reset_write_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/ * pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_lseg (int /*<<< orphan*/ *) ; 

void
filelayout_pg_init_write(struct nfs_pageio_descriptor *pgio,
			 struct nfs_page *req)
{
	struct nfs_commit_info cinfo;
	int status;

	BUG_ON(pgio->pg_lseg != NULL);

	if (req->wb_offset != req->wb_pgbase)
		goto out_mds;
	pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
					   req->wb_context,
					   0,
					   NFS4_MAX_UINT64,
					   IOMODE_RW,
					   GFP_NOFS);
	/* If no lseg, fall back to write through mds */
	if (pgio->pg_lseg == NULL)
		goto out_mds;
	nfs_init_cinfo(&cinfo, pgio->pg_inode, pgio->pg_dreq);
	status = filelayout_alloc_commit_info(pgio->pg_lseg, &cinfo, GFP_NOFS);
	if (status < 0) {
		put_lseg(pgio->pg_lseg);
		pgio->pg_lseg = NULL;
		goto out_mds;
	}
	return;
out_mds:
	nfs_pageio_reset_write_mds(pgio);
}