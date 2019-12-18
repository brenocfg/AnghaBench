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
struct affs_sb_info {int /*<<< orphan*/ * s_bitmap; int /*<<< orphan*/  s_last_bmap; int /*<<< orphan*/ * s_bmap_bh; } ;

/* Variables and functions */
 struct affs_sb_info* AFFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  affs_brelse (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void affs_free_bitmap(struct super_block *sb)
{
	struct affs_sb_info *sbi = AFFS_SB(sb);

	if (!sbi->s_bitmap)
		return;

	affs_brelse(sbi->s_bmap_bh);
	sbi->s_bmap_bh = NULL;
	sbi->s_last_bmap = ~0;
	kfree(sbi->s_bitmap);
	sbi->s_bitmap = NULL;
}