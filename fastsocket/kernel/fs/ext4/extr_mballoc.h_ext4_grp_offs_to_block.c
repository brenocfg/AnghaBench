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
struct ext4_free_extent {int fe_start; scalar_t__ fe_group; } ;
typedef  int ext4_fsblk_t ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_first_data_block; } ;

/* Variables and functions */
 int EXT4_BLOCKS_PER_GROUP (struct super_block*) ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline ext4_fsblk_t ext4_grp_offs_to_block(struct super_block *sb,
					struct ext4_free_extent *fex)
{
	ext4_fsblk_t block;

	block = (ext4_fsblk_t) fex->fe_group * EXT4_BLOCKS_PER_GROUP(sb)
			+ fex->fe_start
			+ le32_to_cpu(EXT4_SB(sb)->s_es->s_first_data_block);
	return block;
}