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
struct inode {TYPE_1__* i_sb; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_2__ {unsigned int s_blocksize; } ;

/* Variables and functions */
 int PAGE_CACHE_SIZE ; 
 int ext4_block_zero_page_range (int /*<<< orphan*/ *,struct address_space*,int,unsigned int) ; 

int ext4_block_truncate_page(handle_t *handle,
		struct address_space *mapping, loff_t from)
{
	unsigned offset = from & (PAGE_CACHE_SIZE-1);
	unsigned length;
	unsigned blocksize;
	struct inode *inode = mapping->host;

	blocksize = inode->i_sb->s_blocksize;
	length = blocksize - (offset & (blocksize - 1));

	return ext4_block_zero_page_range(handle, mapping, from, length);
}