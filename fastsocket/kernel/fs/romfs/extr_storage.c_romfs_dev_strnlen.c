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
struct super_block {scalar_t__ s_bdev; scalar_t__ s_mtd; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  romfs_blk_strnlen (struct super_block*,unsigned long,size_t) ; 
 size_t romfs_maxsize (struct super_block*) ; 
 int /*<<< orphan*/  romfs_mtd_strnlen (struct super_block*,unsigned long,size_t) ; 

ssize_t romfs_dev_strnlen(struct super_block *sb,
			  unsigned long pos, size_t maxlen)
{
	size_t limit;

	limit = romfs_maxsize(sb);
	if (pos >= limit)
		return -EIO;
	if (maxlen > limit - pos)
		maxlen = limit - pos;

#ifdef CONFIG_ROMFS_ON_MTD
	if (sb->s_mtd)
		return romfs_mtd_strnlen(sb, pos, maxlen);
#endif
#ifdef CONFIG_ROMFS_ON_BLOCK
	if (sb->s_bdev)
		return romfs_blk_strnlen(sb, pos, maxlen);
#endif
	return -EIO;
}