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
struct nilfs_inode {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {unsigned int b_data; } ;

/* Variables and functions */
 int nilfs_read_inode_common (struct inode*,struct nilfs_inode*) ; 

__attribute__((used)) static inline int
nilfs_mdt_read_inode_direct(struct inode *inode, struct buffer_head *bh,
			    unsigned n)
{
	return nilfs_read_inode_common(
		inode, (struct nilfs_inode *)(bh->b_data + n));
}