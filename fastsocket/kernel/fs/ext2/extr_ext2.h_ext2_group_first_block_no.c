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
struct super_block {int dummy; } ;
typedef  unsigned long ext2_fsblk_t ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 scalar_t__ EXT2_BLOCKS_PER_GROUP (struct super_block*) ; 
 TYPE_2__* EXT2_SB (struct super_block*) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ext2_fsblk_t
ext2_group_first_block_no(struct super_block *sb, unsigned long group_no)
{
	return group_no * (ext2_fsblk_t)EXT2_BLOCKS_PER_GROUP(sb) +
		le32_to_cpu(EXT2_SB(sb)->s_es->s_first_data_block);
}