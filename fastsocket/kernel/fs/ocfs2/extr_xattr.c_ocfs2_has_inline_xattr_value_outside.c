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
struct ocfs2_xattr_header {int /*<<< orphan*/ * xh_entries; int /*<<< orphan*/  xh_count; } ;
struct ocfs2_dinode {int /*<<< orphan*/  i_xattr_inline_size; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {int s_blocksize; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_is_local (int /*<<< orphan*/ *) ; 

int ocfs2_has_inline_xattr_value_outside(struct inode *inode,
					 struct ocfs2_dinode *di)
{
	struct ocfs2_xattr_header *xh;
	int i;

	xh = (struct ocfs2_xattr_header *)
		 ((void *)di + inode->i_sb->s_blocksize -
		 le16_to_cpu(di->i_xattr_inline_size));

	for (i = 0; i < le16_to_cpu(xh->xh_count); i++)
		if (!ocfs2_xattr_is_local(&xh->xh_entries[i]))
			return 1;

	return 0;
}