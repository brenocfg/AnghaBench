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
struct TYPE_2__ {int /*<<< orphan*/  i_lock; } ;
struct nfs_inode {TYPE_1__ vfs_inode; struct pnfs_layout_hdr* layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_matching_lsegs_invalid (struct pnfs_layout_hdr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pnfs_free_lseg_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_list ; 

void
pnfs_destroy_layout(struct nfs_inode *nfsi)
{
	struct pnfs_layout_hdr *lo;
	LIST_HEAD(tmp_list);

	spin_lock(&nfsi->vfs_inode.i_lock);
	lo = nfsi->layout;
	if (lo) {
		lo->plh_block_lgets++; /* permanently block new LAYOUTGETs */
		mark_matching_lsegs_invalid(lo, &tmp_list, NULL);
	}
	spin_unlock(&nfsi->vfs_inode.i_lock);
	pnfs_free_lseg_list(&tmp_list);
}