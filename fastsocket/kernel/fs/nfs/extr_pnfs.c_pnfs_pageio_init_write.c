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
struct pnfs_layoutdriver_type {int /*<<< orphan*/  pg_write_ops; } ;
struct nfs_server {int /*<<< orphan*/  wsize; struct pnfs_layoutdriver_type* pnfs_curr_ld; } ;
struct nfs_pgio_completion_ops {int dummy; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs_pageio_init (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ ,struct nfs_pgio_completion_ops const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_pageio_init_write (struct nfs_pageio_descriptor*,struct inode*,int,struct nfs_pgio_completion_ops const*) ; 

void
pnfs_pageio_init_write(struct nfs_pageio_descriptor *pgio, struct inode *inode,
		       int ioflags,
		       const struct nfs_pgio_completion_ops *compl_ops)
{
	struct nfs_server *server = NFS_SERVER(inode);
	struct pnfs_layoutdriver_type *ld = server->pnfs_curr_ld;

	if (ld == NULL)
		nfs_pageio_init_write(pgio, inode, ioflags, compl_ops);
	else
		nfs_pageio_init(pgio, inode, ld->pg_write_ops, compl_ops, server->wsize, ioflags);
}