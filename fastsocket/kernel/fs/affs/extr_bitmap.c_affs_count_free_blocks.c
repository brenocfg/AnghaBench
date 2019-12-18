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
typedef  scalar_t__ u32 ;
struct super_block {int s_flags; } ;
struct affs_bm_info {scalar_t__ bm_free; } ;
struct TYPE_2__ {int s_bmap_count; int /*<<< orphan*/  s_bmlock; struct affs_bm_info* s_bitmap; } ;

/* Variables and functions */
 TYPE_1__* AFFS_SB (struct super_block*) ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

u32
affs_count_free_blocks(struct super_block *sb)
{
	struct affs_bm_info *bm;
	u32 free;
	int i;

	pr_debug("AFFS: count_free_blocks()\n");

	if (sb->s_flags & MS_RDONLY)
		return 0;

	mutex_lock(&AFFS_SB(sb)->s_bmlock);

	bm = AFFS_SB(sb)->s_bitmap;
	free = 0;
	for (i = AFFS_SB(sb)->s_bmap_count; i > 0; bm++, i--)
		free += bm->bm_free;

	mutex_unlock(&AFFS_SB(sb)->s_bmlock);

	return free;
}