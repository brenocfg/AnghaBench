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
struct sysv_sb_info {scalar_t__ s_forced_ro; } ;
struct super_block {int s_dirt; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  lock_super (struct super_block*) ; 
 int /*<<< orphan*/  unlock_super (struct super_block*) ; 

__attribute__((used)) static int sysv_remount(struct super_block *sb, int *flags, char *data)
{
	struct sysv_sb_info *sbi = SYSV_SB(sb);
	lock_super(sb);
	if (sbi->s_forced_ro)
		*flags |= MS_RDONLY;
	if (!(*flags & MS_RDONLY))
		sb->s_dirt = 1;
	unlock_super(sb);
	return 0;
}