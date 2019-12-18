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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_block_lgets; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;
struct TYPE_2__ {struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  pnfs_put_layout_hdr_locked (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void pnfs_roc_release(struct inode *ino)
{
	struct pnfs_layout_hdr *lo;

	spin_lock(&ino->i_lock);
	lo = NFS_I(ino)->layout;
	lo->plh_block_lgets--;
	pnfs_put_layout_hdr_locked(lo);
	spin_unlock(&ino->i_lock);
}