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
struct ext3_sb_info {scalar_t__ s_resuid; scalar_t__ s_resgid; TYPE_1__* s_es; int /*<<< orphan*/  s_freeblocks_counter; } ;
typedef  scalar_t__ ext3_fsblk_t ;
struct TYPE_2__ {int /*<<< orphan*/  s_r_blocks_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_fsuid () ; 
 int /*<<< orphan*/  in_group_p (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ percpu_counter_read_positive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext3_has_free_blocks(struct ext3_sb_info *sbi)
{
	ext3_fsblk_t free_blocks, root_blocks;

	free_blocks = percpu_counter_read_positive(&sbi->s_freeblocks_counter);
	root_blocks = le32_to_cpu(sbi->s_es->s_r_blocks_count);
	if (free_blocks < root_blocks + 1 && !capable(CAP_SYS_RESOURCE) &&
		sbi->s_resuid != current_fsuid() &&
		(sbi->s_resgid == 0 || !in_group_p (sbi->s_resgid))) {
		return 0;
	}
	return 1;
}