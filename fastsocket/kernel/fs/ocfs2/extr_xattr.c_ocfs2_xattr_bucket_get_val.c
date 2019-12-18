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
struct ocfs2_xattr_bucket {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {int s_blocksize_bits; int s_blocksize; } ;

/* Variables and functions */
 char* bucket_block (struct ocfs2_xattr_bucket*,int) ; 

__attribute__((used)) static inline char *ocfs2_xattr_bucket_get_val(struct inode *inode,
					struct ocfs2_xattr_bucket *bucket,
					int offs)
{
	int block_off = offs >> inode->i_sb->s_blocksize_bits;

	offs = offs % inode->i_sb->s_blocksize;
	return bucket_block(bucket, block_off) + offs;
}