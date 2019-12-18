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
struct ext4_li_request {scalar_t__ lr_next_group; long lr_timeout; unsigned long lr_next_sched; TYPE_1__* lr_sbi; struct super_block* lr_super; } ;
struct ext4_group_desc {int bg_flags; } ;
typedef  scalar_t__ ext4_group_t ;
struct TYPE_4__ {scalar_t__ s_groups_count; } ;
struct TYPE_3__ {unsigned long s_li_wait_mult; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT4_BG_INODE_ZEROED ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 int ext4_init_inode_table (struct super_block*,scalar_t__,int) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  sb_end_write (struct super_block*) ; 
 int /*<<< orphan*/  sb_start_write (struct super_block*) ; 

__attribute__((used)) static int ext4_run_li_request(struct ext4_li_request *elr)
{
	struct ext4_group_desc *gdp = NULL;
	ext4_group_t group, ngroups;
	struct super_block *sb;
	unsigned long timeout = 0;
	int ret = 0;

	sb = elr->lr_super;
	ngroups = EXT4_SB(sb)->s_groups_count;

	sb_start_write(sb);
	for (group = elr->lr_next_group; group < ngroups; group++) {
		gdp = ext4_get_group_desc(sb, group, NULL);
		if (!gdp) {
			ret = 1;
			break;
		}

		if (!(gdp->bg_flags & cpu_to_le16(EXT4_BG_INODE_ZEROED)))
			break;
	}

	if (group == ngroups)
		ret = 1;

	if (!ret) {
		timeout = jiffies;
		ret = ext4_init_inode_table(sb, group,
					    elr->lr_timeout ? 0 : 1);
		if (elr->lr_timeout == 0) {
			timeout = (jiffies - timeout) *
				  elr->lr_sbi->s_li_wait_mult;
			elr->lr_timeout = timeout;
		}
		elr->lr_next_sched = jiffies + elr->lr_timeout;
		elr->lr_next_group = group + 1;
	}
	sb_end_write(sb);

	return ret;
}