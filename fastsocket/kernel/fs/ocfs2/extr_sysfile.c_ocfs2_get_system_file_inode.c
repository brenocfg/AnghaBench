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
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_super {struct inode** system_inodes; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct inode* _ocfs2_get_system_file_inode (struct ocfs2_super*,int,int /*<<< orphan*/ ) ; 
 struct inode* igrab (struct inode*) ; 
 scalar_t__ is_in_system_inode_array (struct ocfs2_super*,int,int /*<<< orphan*/ ) ; 

struct inode *ocfs2_get_system_file_inode(struct ocfs2_super *osb,
					  int type,
					  u32 slot)
{
	struct inode *inode = NULL;
	struct inode **arr = NULL;

	/* avoid the lookup if cached in local system file array */
	if (is_in_system_inode_array(osb, type, slot))
		arr = &(osb->system_inodes[type]);

	if (arr && ((inode = *arr) != NULL)) {
		/* get a ref in addition to the array ref */
		inode = igrab(inode);
		BUG_ON(!inode);

		return inode;
	}

	/* this gets one ref thru iget */
	inode = _ocfs2_get_system_file_inode(osb, type, slot);

	/* add one more if putting into array for first time */
	if (arr && inode) {
		*arr = igrab(inode);
		BUG_ON(!*arr);
	}
	return inode;
}