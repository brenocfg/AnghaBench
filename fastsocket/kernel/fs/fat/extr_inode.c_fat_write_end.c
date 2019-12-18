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
struct page {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct file {int dummy; } ;
struct address_space {struct inode* host; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int i_attrs; } ;

/* Variables and functions */
 int ATTR_ARCH ; 
 int /*<<< orphan*/  CURRENT_TIME_SEC ; 
 TYPE_1__* MSDOS_I (struct inode*) ; 
 int generic_write_end (struct file*,struct address_space*,int /*<<< orphan*/ ,unsigned int,unsigned int,struct page*,void*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static int fat_write_end(struct file *file, struct address_space *mapping,
			loff_t pos, unsigned len, unsigned copied,
			struct page *pagep, void *fsdata)
{
	struct inode *inode = mapping->host;
	int err;
	err = generic_write_end(file, mapping, pos, len, copied, pagep, fsdata);
	if (!(err < 0) && !(MSDOS_I(inode)->i_attrs & ATTR_ARCH)) {
		inode->i_mtime = inode->i_ctime = CURRENT_TIME_SEC;
		MSDOS_I(inode)->i_attrs |= ATTR_ARCH;
		mark_inode_dirty(inode);
	}
	return err;
}