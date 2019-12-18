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
struct pnfs_layout_hdr {int dummy; } ;
struct pnfs_ds_commit_info {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_4__ {struct pnfs_ds_commit_info commit_info; } ;
struct TYPE_3__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 TYPE_2__* FILELAYOUT_FROM_HDR (struct pnfs_layout_hdr*) ; 
 TYPE_1__* NFS_I (struct inode*) ; 

__attribute__((used)) static struct pnfs_ds_commit_info *
filelayout_get_ds_info(struct inode *inode)
{
	struct pnfs_layout_hdr *layout = NFS_I(inode)->layout;

	if (layout == NULL)
		return NULL;
	else
		return &FILELAYOUT_FROM_HDR(layout)->commit_info;
}