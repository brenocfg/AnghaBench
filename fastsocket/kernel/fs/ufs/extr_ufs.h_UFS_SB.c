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
struct ufs_sb_info {int dummy; } ;
struct super_block {struct ufs_sb_info* s_fs_info; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ufs_sb_info *UFS_SB(struct super_block *sb)
{
	return sb->s_fs_info;
}