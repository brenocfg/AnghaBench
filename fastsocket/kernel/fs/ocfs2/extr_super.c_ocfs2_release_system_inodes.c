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
struct ocfs2_super {struct inode* root_inode; struct inode* sys_root_inode; struct inode** system_inodes; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int NUM_SYSTEM_INODES ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_release_system_inodes(struct ocfs2_super *osb)
{
	int i;
	struct inode *inode;

	mlog_entry_void();

	for (i = 0; i < NUM_SYSTEM_INODES; i++) {
		inode = osb->system_inodes[i];
		if (inode) {
			iput(inode);
			osb->system_inodes[i] = NULL;
		}
	}

	inode = osb->sys_root_inode;
	if (inode) {
		iput(inode);
		osb->sys_root_inode = NULL;
	}

	inode = osb->root_inode;
	if (inode) {
		iput(inode);
		osb->root_inode = NULL;
	}

	mlog_exit(0);
}