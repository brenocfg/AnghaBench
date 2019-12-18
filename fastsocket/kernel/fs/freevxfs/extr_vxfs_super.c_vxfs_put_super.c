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
struct vxfs_sb_info {int /*<<< orphan*/  vsi_bp; int /*<<< orphan*/  vsi_stilist; int /*<<< orphan*/  vsi_ilist; int /*<<< orphan*/  vsi_fship; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 struct vxfs_sb_info* VXFS_SBI (struct super_block*) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vxfs_sb_info*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  vxfs_put_fake_inode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vxfs_put_super(struct super_block *sbp)
{
	struct vxfs_sb_info	*infp = VXFS_SBI(sbp);

	lock_kernel();

	vxfs_put_fake_inode(infp->vsi_fship);
	vxfs_put_fake_inode(infp->vsi_ilist);
	vxfs_put_fake_inode(infp->vsi_stilist);

	brelse(infp->vsi_bp);
	kfree(infp);

	unlock_kernel();
}