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
struct jfs_inode_info {int active_ag; int agno; int /*<<< orphan*/  ag_lock; } ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct file {int f_mode; } ;
struct TYPE_4__ {TYPE_1__* bmap; } ;
struct TYPE_3__ {int /*<<< orphan*/ * db_active; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 TYPE_2__* JFS_SBI (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int generic_file_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jfs_open(struct inode *inode, struct file *file)
{
	int rc;

	if ((rc = generic_file_open(inode, file)))
		return rc;

	/*
	 * We attempt to allow only one "active" file open per aggregate
	 * group.  Otherwise, appending to files in parallel can cause
	 * fragmentation within the files.
	 *
	 * If the file is empty, it was probably just created and going
	 * to be written to.  If it has a size, we'll hold off until the
	 * file is actually grown.
	 */
	if (S_ISREG(inode->i_mode) && file->f_mode & FMODE_WRITE &&
	    (inode->i_size == 0)) {
		struct jfs_inode_info *ji = JFS_IP(inode);
		spin_lock_irq(&ji->ag_lock);
		if (ji->active_ag == -1) {
			ji->active_ag = ji->agno;
			atomic_inc(
			    &JFS_SBI(inode->i_sb)->bmap->db_active[ji->agno]);
		}
		spin_unlock_irq(&ji->ag_lock);
	}

	return 0;
}