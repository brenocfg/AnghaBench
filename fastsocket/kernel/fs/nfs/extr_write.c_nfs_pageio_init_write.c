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
struct nfs_pgio_completion_ops {int dummy; } ;
struct nfs_pageio_descriptor {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wsize; } ;

/* Variables and functions */
 TYPE_1__* NFS_SERVER (struct inode*) ; 
 int /*<<< orphan*/  nfs_pageio_init (struct nfs_pageio_descriptor*,struct inode*,int /*<<< orphan*/ *,struct nfs_pgio_completion_ops const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_pageio_write_ops ; 

void nfs_pageio_init_write(struct nfs_pageio_descriptor *pgio,
			       struct inode *inode, int ioflags,
			       const struct nfs_pgio_completion_ops *compl_ops)
{
	nfs_pageio_init(pgio, inode, &nfs_pageio_write_ops, compl_ops,
				NFS_SERVER(inode)->wsize, ioflags);
}