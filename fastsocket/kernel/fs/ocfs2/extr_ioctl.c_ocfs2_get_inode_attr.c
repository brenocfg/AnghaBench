#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {unsigned int ip_attr; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  ocfs2_get_inode_flags (TYPE_1__*) ; 
 int ocfs2_inode_lock (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_get_inode_attr(struct inode *inode, unsigned *flags)
{
	int status;

	status = ocfs2_inode_lock(inode, NULL, 0);
	if (status < 0) {
		mlog_errno(status);
		return status;
	}
	ocfs2_get_inode_flags(OCFS2_I(inode));
	*flags = OCFS2_I(inode)->ip_attr;
	ocfs2_inode_unlock(inode, 0);

	mlog_exit(status);
	return status;
}