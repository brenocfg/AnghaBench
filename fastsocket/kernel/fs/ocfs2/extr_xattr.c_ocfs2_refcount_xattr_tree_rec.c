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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ocfs2_iterate_xattr_buckets (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_value_refcount ; 

__attribute__((used)) static int ocfs2_refcount_xattr_tree_rec(struct inode *inode,
				     struct buffer_head *root_bh,
				     u64 blkno, u32 cpos, u32 len, void *para)
{
	return ocfs2_iterate_xattr_buckets(inode, blkno, len,
					   ocfs2_xattr_bucket_value_refcount,
					   para);
}