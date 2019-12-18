#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct flex_groups {int dummy; } ;
struct ext4_sb_info {int s_log_groups_per_flex; unsigned int s_groups_count; TYPE_2__* s_flex_groups; TYPE_1__* s_es; } ;
struct ext4_group_desc {int dummy; } ;
typedef  int ext4_group_t ;
struct TYPE_6__ {int /*<<< orphan*/  used_dirs; int /*<<< orphan*/  free_blocks; int /*<<< orphan*/  free_inodes; } ;
struct TYPE_5__ {int s_log_groups_per_flex; int /*<<< orphan*/  s_reserved_gdt_blocks; } ;

/* Variables and functions */
 int EXT4_DESC_PER_BLOCK_BITS (struct super_block*) ; 
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  atomic_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ext4_flex_group (struct ext4_sb_info*,int) ; 
 int /*<<< orphan*/  ext4_free_blks_count (struct super_block*,struct ext4_group_desc*) ; 
 int /*<<< orphan*/  ext4_free_inodes_count (struct super_block*,struct ext4_group_desc*) ; 
 struct ext4_group_desc* ext4_get_group_desc (struct super_block*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ext4_used_dirs_count (struct super_block*,struct ext4_group_desc*) ; 
 TYPE_2__* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_2__* vmalloc (size_t) ; 

__attribute__((used)) static int ext4_fill_flex_info(struct super_block *sb)
{
	struct ext4_sb_info *sbi = EXT4_SB(sb);
	struct ext4_group_desc *gdp = NULL;
	ext4_group_t flex_group_count;
	ext4_group_t flex_group;
	unsigned int groups_per_flex = 0;
	size_t size;
	int i;

	sbi->s_log_groups_per_flex = sbi->s_es->s_log_groups_per_flex;
	if (sbi->s_log_groups_per_flex < 1 || sbi->s_log_groups_per_flex > 31) {
		sbi->s_log_groups_per_flex = 0;
		return 1;
	}
	groups_per_flex = 1U << sbi->s_log_groups_per_flex;

	/* We allocate both existing and potentially added groups */
	flex_group_count = ((sbi->s_groups_count + groups_per_flex - 1) +
			((le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks) + 1) <<
			      EXT4_DESC_PER_BLOCK_BITS(sb))) / groups_per_flex;
	size = flex_group_count * sizeof(struct flex_groups);
	sbi->s_flex_groups = kzalloc(size, GFP_KERNEL);
	if (sbi->s_flex_groups == NULL) {
		sbi->s_flex_groups = vmalloc(size);
		if (sbi->s_flex_groups)
			memset(sbi->s_flex_groups, 0, size);
	}
	if (sbi->s_flex_groups == NULL) {
		ext4_msg(sb, KERN_ERR, "not enough memory for "
				"%u flex groups", flex_group_count);
		goto failed;
	}

	for (i = 0; i < sbi->s_groups_count; i++) {
		gdp = ext4_get_group_desc(sb, i, NULL);

		flex_group = ext4_flex_group(sbi, i);
		atomic_add(ext4_free_inodes_count(sb, gdp),
			   &sbi->s_flex_groups[flex_group].free_inodes);
		atomic_add(ext4_free_blks_count(sb, gdp),
			   &sbi->s_flex_groups[flex_group].free_blocks);
		atomic_add(ext4_used_dirs_count(sb, gdp),
			   &sbi->s_flex_groups[flex_group].used_dirs);
	}

	return 1;
failed:
	return 0;
}