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
typedef  unsigned long long u64 ;
struct super_block {int dummy; } ;
struct nilfs_super_block {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 unsigned long do_div (unsigned long long,int) ; 
 struct buffer_head* sb_bread (struct super_block*,unsigned long long) ; 

struct nilfs_super_block *nilfs_read_super_block(struct super_block *sb,
						 u64 pos, int blocksize,
						 struct buffer_head **pbh)
{
	unsigned long long sb_index = pos;
	unsigned long offset;

	offset = do_div(sb_index, blocksize);
	*pbh = sb_bread(sb, sb_index);
	if (!*pbh)
		return NULL;
	return (struct nilfs_super_block *)((char *)(*pbh)->b_data + offset);
}