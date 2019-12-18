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
struct super_block {int dummy; } ;
struct ext4_sb_info {int dummy; } ;
struct ext4_li_request {scalar_t__ lr_next_sched; int /*<<< orphan*/  lr_next_group; struct ext4_sb_info* lr_sbi; struct super_block* lr_super; } ;
typedef  int /*<<< orphan*/  rnd ;
typedef  int /*<<< orphan*/  ext4_group_t ;

/* Variables and functions */
 unsigned long EXT4_DEF_LI_MAX_START_DELAY ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  get_random_bytes (unsigned long*,int) ; 
 scalar_t__ jiffies ; 
 struct ext4_li_request* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ext4_li_request *ext4_li_request_new(struct super_block *sb,
					    ext4_group_t start)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_li_request *elr;
	unsigned long rnd;

	elr = kzalloc(sizeof(*elr), GFP_KERNEL);
	if (!elr)
		return NULL;

	elr->lr_super = sb;
	elr->lr_sbi = sbi;
	elr->lr_next_group = start;

	/*
	 * Randomize first schedule time of the request to
	 * spread the inode table initialization requests
	 * better.
	 */
	get_random_bytes(&rnd, sizeof(rnd));
	elr->lr_next_sched = jiffies + (unsigned long)rnd %
			     (EXT4_DEF_LI_MAX_START_DELAY * HZ);

	return elr;
}