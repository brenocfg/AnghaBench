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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int bh_offset (struct buffer_head const*) ; 

__attribute__((used)) static unsigned char *
nilfs_palloc_block_get_bitmap(const struct inode *inode,
			      const struct buffer_head *bh, void *kaddr)
{
	return (unsigned char *)(kaddr + bh_offset(bh));
}