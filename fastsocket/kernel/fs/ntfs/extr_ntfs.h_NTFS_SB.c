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
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
typedef  int /*<<< orphan*/  ntfs_volume ;

/* Variables and functions */

__attribute__((used)) static inline ntfs_volume *NTFS_SB(struct super_block *sb)
{
	return sb->s_fs_info;
}