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
struct pnfs_layout_hdr {int /*<<< orphan*/  plh_refcount; struct inode* plh_inode; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_layout_hdr (struct pnfs_layout_hdr*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
pnfs_put_layout_hdr(struct pnfs_layout_hdr *lo)
{
	struct inode *inode = lo->plh_inode;

	if (atomic_dec_and_lock(&lo->plh_refcount, &inode->i_lock)) {
		destroy_layout_hdr(lo);
		spin_unlock(&inode->i_lock);
	}
}