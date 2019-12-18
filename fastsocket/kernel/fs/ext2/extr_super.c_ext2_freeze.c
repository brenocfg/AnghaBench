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
struct super_block {int dummy; } ;
struct ext2_sb_info {TYPE_1__* s_es; int /*<<< orphan*/  s_mount_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_state; } ;

/* Variables and functions */
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext2_sync_super (struct super_block*,TYPE_1__*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int ext2_freeze(struct super_block *sb)
{
	struct ext2_sb_info *sbi = EXT2_SB(sb);

	/* Set EXT2_FS_VALID flag */
	lock_kernel();
	sbi->s_es->s_state = cpu_to_le16(sbi->s_mount_state);
	unlock_kernel();
	ext2_sync_super(sb, sbi->s_es);

	return 0;
}