#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mtd_info {unsigned long (* get_unmapped_area ) (struct mtd_info*,unsigned long,unsigned long,unsigned long) ;unsigned long size; } ;
struct inode {TYPE_2__* i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_6__ {scalar_t__ i_dataoffset; } ;
struct TYPE_5__ {struct mtd_info* s_mtd; } ;
struct TYPE_4__ {struct inode* host; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 unsigned long PAGE_SHIFT ; 
 TYPE_3__* ROMFS_I (struct inode*) ; 
 unsigned long i_size_read (struct inode*) ; 
 unsigned long stub1 (struct mtd_info*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long romfs_get_unmapped_area(struct file *file,
					     unsigned long addr,
					     unsigned long len,
					     unsigned long pgoff,
					     unsigned long flags)
{
	struct inode *inode = file->f_mapping->host;
	struct mtd_info *mtd = inode->i_sb->s_mtd;
	unsigned long isize, offset;

	if (!mtd)
		goto cant_map_directly;

	isize = i_size_read(inode);
	offset = pgoff << PAGE_SHIFT;
	if (offset > isize || len > isize || offset > isize - len)
		return (unsigned long) -EINVAL;

	/* we need to call down to the MTD layer to do the actual mapping */
	if (mtd->get_unmapped_area) {
		if (addr != 0)
			return (unsigned long) -EINVAL;

		if (len > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
			return (unsigned long) -EINVAL;

		offset += ROMFS_I(inode)->i_dataoffset;
		if (offset > mtd->size - len)
			return (unsigned long) -EINVAL;

		return mtd->get_unmapped_area(mtd, len, offset, flags);
	}

cant_map_directly:
	return (unsigned long) -ENOSYS;
}