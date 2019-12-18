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
struct TYPE_2__ {scalar_t__ i_symlink; } ;
struct ocfs2_dinode {TYPE_1__ id2; } ;
struct inode {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  mlog_entry_void () ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int ocfs2_read_inode_block (struct inode*,struct buffer_head**) ; 

__attribute__((used)) static char *ocfs2_fast_symlink_getlink(struct inode *inode,
					struct buffer_head **bh)
{
	int status;
	char *link = NULL;
	struct ocfs2_dinode *fe;

	mlog_entry_void();

	status = ocfs2_read_inode_block(inode, bh);
	if (status < 0) {
		mlog_errno(status);
		link = ERR_PTR(status);
		goto bail;
	}

	fe = (struct ocfs2_dinode *) (*bh)->b_data;
	link = (char *) fe->id2.i_symlink;
bail:
	mlog_exit(status);

	return link;
}