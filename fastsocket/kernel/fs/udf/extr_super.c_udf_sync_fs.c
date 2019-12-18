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
struct udf_sb_info {int /*<<< orphan*/  s_alloc_mutex; scalar_t__ s_lvid_dirty; int /*<<< orphan*/  s_lvid_bh; } ;
struct super_block {scalar_t__ s_dirt; } ;

/* Variables and functions */
 struct udf_sb_info* UDF_SB (struct super_block*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int udf_sync_fs(struct super_block *sb, int wait)
{
	struct udf_sb_info *sbi = UDF_SB(sb);

	mutex_lock(&sbi->s_alloc_mutex);
	if (sbi->s_lvid_dirty) {
		/*
		 * Blockdevice will be synced later so we don't have to submit
		 * the buffer for IO
		 */
		mark_buffer_dirty(sbi->s_lvid_bh);
		sb->s_dirt = 0;
		sbi->s_lvid_dirty = 0;
	}
	mutex_unlock(&sbi->s_alloc_mutex);

	return 0;
}