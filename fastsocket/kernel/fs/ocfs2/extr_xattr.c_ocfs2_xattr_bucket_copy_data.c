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
struct ocfs2_xattr_bucket {int bu_blocks; TYPE_2__* bu_inode; } ;
struct TYPE_4__ {TYPE_1__* i_sb; } ;
struct TYPE_3__ {int s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bucket_block (struct ocfs2_xattr_bucket*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ocfs2_xattr_bucket_copy_data(struct ocfs2_xattr_bucket *dest,
					 struct ocfs2_xattr_bucket *src)
{
	int i;
	int blocksize = src->bu_inode->i_sb->s_blocksize;

	BUG_ON(dest->bu_blocks != src->bu_blocks);
	BUG_ON(dest->bu_inode != src->bu_inode);

	for (i = 0; i < src->bu_blocks; i++) {
		memcpy(bucket_block(dest, i), bucket_block(src, i),
		       blocksize);
	}
}