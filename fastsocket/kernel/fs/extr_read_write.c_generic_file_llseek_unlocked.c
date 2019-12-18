#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_size; } ;
struct file {scalar_t__ f_pos; scalar_t__ f_version; TYPE_2__* f_mapping; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {struct inode* host; } ;
struct TYPE_3__ {scalar_t__ s_maxbytes; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
#define  SEEK_CUR 129 
#define  SEEK_END 128 

loff_t
generic_file_llseek_unlocked(struct file *file, loff_t offset, int origin)
{
	struct inode *inode = file->f_mapping->host;

	switch (origin) {
	case SEEK_END:
		offset += inode->i_size;
		break;
	case SEEK_CUR:
		/*
		 * Here we special-case the lseek(fd, 0, SEEK_CUR)
		 * position-querying operation.  Avoid rewriting the "same"
		 * f_pos value back to the file because a concurrent read(),
		 * write() or lseek() might have altered it
		 */
		if (offset == 0)
			return file->f_pos;
		offset += file->f_pos;
		break;
	}

	if (offset < 0 || offset > inode->i_sb->s_maxbytes)
		return -EINVAL;

	/* Special lock needed here? */
	if (offset != file->f_pos) {
		file->f_pos = offset;
		file->f_version = 0;
	}

	return offset;
}