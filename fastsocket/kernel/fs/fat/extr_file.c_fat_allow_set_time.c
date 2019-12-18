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
struct TYPE_2__ {int allow_utime; } ;
struct msdos_sb_info {TYPE_1__ options; } ;
struct inode {scalar_t__ i_uid; int /*<<< orphan*/  i_gid; } ;
typedef  int mode_t ;

/* Variables and functions */
 int MAY_WRITE ; 
 scalar_t__ current_fsuid () ; 
 scalar_t__ in_group_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fat_allow_set_time(struct msdos_sb_info *sbi, struct inode *inode)
{
	mode_t allow_utime = sbi->options.allow_utime;

	if (current_fsuid() != inode->i_uid) {
		if (in_group_p(inode->i_gid))
			allow_utime >>= 3;
		if (allow_utime & MAY_WRITE)
			return 1;
	}

	/* use a default check */
	return 0;
}