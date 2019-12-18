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
struct pnfs_layoutdriver_type {void (* free_layout_hdr ) (struct pnfs_layout_hdr*) ;scalar_t__ alloc_layout_hdr; } ;
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_lc_cred; int /*<<< orphan*/  plh_inode; } ;
struct TYPE_2__ {struct pnfs_layoutdriver_type* pnfs_curr_ld; } ;

/* Variables and functions */
 TYPE_1__* NFS_SERVER (int /*<<< orphan*/ ) ; 
 void kfree (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 
 void stub1 (struct pnfs_layout_hdr*) ; 

__attribute__((used)) static void
pnfs_free_layout_hdr(struct pnfs_layout_hdr *lo)
{
	struct pnfs_layoutdriver_type *ld = NFS_SERVER(lo->plh_inode)->pnfs_curr_ld;
	put_rpccred(lo->plh_lc_cred);
	return ld->alloc_layout_hdr ? ld->free_layout_hdr(lo) : kfree(lo);
}