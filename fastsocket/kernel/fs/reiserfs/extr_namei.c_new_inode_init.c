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
struct inode {int i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct TYPE_2__ {scalar_t__ k_objectid; } ;

/* Variables and functions */
 TYPE_1__* INODE_PKEY (struct inode*) ; 
 scalar_t__ S_ISDIR (int) ; 
 int S_ISGID ; 
 int /*<<< orphan*/  current_fsgid () ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__attribute__((used)) static int new_inode_init(struct inode *inode, struct inode *dir, int mode)
{

	/* the quota init calls have to know who to charge the quota to, so
	 ** we have to set uid and gid here
	 */
	inode->i_uid = current_fsuid();
	inode->i_mode = mode;
	/* Make inode invalid - just in case we are going to drop it before
	 * the initialization happens */
	INODE_PKEY(inode)->k_objectid = 0;

	if (dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			inode->i_mode |= S_ISGID;
	} else {
		inode->i_gid = current_fsgid();
	}
	vfs_dq_init(inode);
	return 0;
}