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

/* Variables and functions */
 int EIO ; 
 int romfs_blk_read (struct super_block*,unsigned long,void*,size_t) ; 
 size_t romfs_maxsize (struct super_block*) ; 
 int romfs_mtd_read (struct super_block*,unsigned long,void*,size_t) ; 

int romfs_dev_read(struct super_block *sb, unsigned long pos,
		   void *buf, size_t buflen)
{
	size_t limit;

	limit = romfs_maxsize(sb);
	if (pos >= limit)
		return -EIO;
	if (buflen > limit - pos)
		buflen = limit - pos;

#ifdef CONFIG_ROMFS_ON_MTD
	if (sb->s_mtd)
		return romfs_mtd_read(sb, pos, buf, buflen);
#endif
#ifdef CONFIG_ROMFS_ON_BLOCK
	if (sb->s_bdev)
		return romfs_blk_read(sb, pos, buf, buflen);
#endif
	return -EIO;
}