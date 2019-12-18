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
struct ext4_sb_info {int /*<<< orphan*/  s_resv_blocks; int /*<<< orphan*/  s_es; } ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ext4_blocks_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_reserve_blocks(struct ext4_sb_info *sbi, ext4_fsblk_t count)
{
	ext4_fsblk_t blocks = ext4_blocks_count(sbi->s_es);

	if (count >= blocks)
		return -EINVAL;

	atomic64_set(&sbi->s_resv_blocks, count);
	return 0;
}