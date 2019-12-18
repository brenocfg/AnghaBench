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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int s_reserved; int s_partition_size; } ;

/* Variables and functions */
 TYPE_1__* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct buffer_head* sb_getblk (struct super_block*,int) ; 

__attribute__((used)) static inline struct buffer_head *
affs_getblk(struct super_block *sb, int block)
{
	pr_debug("affs_getblk: %d\n", block);
	if (block >= AFFS_SB(sb)->s_reserved && block < AFFS_SB(sb)->s_partition_size)
		return sb_getblk(sb, block);
	return NULL;
}