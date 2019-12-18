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
struct super_block {int dummy; } ;
struct ocfs2_xattr_value_root {int dummy; } ;
struct ocfs2_xattr_header {int dummy; } ;
struct ocfs2_xattr_bucket {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ocfs2_get_xattr_tree_value_root (struct super_block*,struct ocfs2_xattr_bucket*,int,struct ocfs2_xattr_value_root**,struct buffer_head**) ; 

__attribute__((used)) static int ocfs2_value_tree_metas_in_bucket(struct super_block *sb,
					struct buffer_head *bh,
					struct ocfs2_xattr_header *xh,
					int offset,
					struct ocfs2_xattr_value_root **xv,
					struct buffer_head **ret_bh,
					void *para)
{
	struct ocfs2_xattr_bucket *bucket =
				(struct ocfs2_xattr_bucket *)para;

	return ocfs2_get_xattr_tree_value_root(sb, bucket, offset,
					       xv, ret_bh);
}