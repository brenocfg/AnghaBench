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
struct nfs_pageio_descriptor {int /*<<< orphan*/ * pg_lseg; int /*<<< orphan*/  pg_inode; } ;
struct nfs_page {scalar_t__ wb_offset; scalar_t__ wb_pgbase; int /*<<< orphan*/  wb_bytes; int /*<<< orphan*/  wb_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IOMODE_READ ; 
 int /*<<< orphan*/  nfs_pageio_reset_read_mds (struct nfs_pageio_descriptor*) ; 
 int /*<<< orphan*/ * pnfs_update_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_offset (struct nfs_page*) ; 

void
pnfs_generic_pg_init_read(struct nfs_pageio_descriptor *pgio, struct nfs_page *req)
{
	BUG_ON(pgio->pg_lseg != NULL);

	if (req->wb_offset != req->wb_pgbase) {
		nfs_pageio_reset_read_mds(pgio);
		return;
	}
	pgio->pg_lseg = pnfs_update_layout(pgio->pg_inode,
					   req->wb_context,
					   req_offset(req),
					   req->wb_bytes,
					   IOMODE_READ,
					   GFP_KERNEL);
	/* If no lseg, fall back to read through mds */
	if (pgio->pg_lseg == NULL)
		nfs_pageio_reset_read_mds(pgio);

}