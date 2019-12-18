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
struct TYPE_2__ {int fs_dmask; int fs_fmask; int /*<<< orphan*/  rodir; } ;
struct msdos_sb_info {TYPE_1__ options; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; } ;
typedef  int mode_t ;

/* Variables and functions */
 struct msdos_sb_info* MSDOS_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_IWUGO ; 

__attribute__((used)) static inline int fat_mode_can_hold_ro(struct inode *inode)
{
	struct msdos_sb_info *sbi = MSDOS_SB(inode->i_sb);
	mode_t mask;

	if (S_ISDIR(inode->i_mode)) {
		if (!sbi->options.rodir)
			return 0;
		mask = ~sbi->options.fs_dmask;
	} else
		mask = ~sbi->options.fs_fmask;

	if (!(mask & S_IWUGO))
		return 0;
	return 1;
}