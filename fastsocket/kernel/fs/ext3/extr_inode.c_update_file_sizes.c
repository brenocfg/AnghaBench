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
struct inode {unsigned int i_size; } ;
typedef  unsigned int loff_t ;
struct TYPE_2__ {unsigned int i_disksize; } ;

/* Variables and functions */
 TYPE_1__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,unsigned int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 

__attribute__((used)) static void update_file_sizes(struct inode *inode, loff_t pos, unsigned copied)
{
	/* What matters to us is i_disksize. We don't write i_size anywhere */
	if (pos + copied > inode->i_size)
		i_size_write(inode, pos + copied);
	if (pos + copied > EXT3_I(inode)->i_disksize) {
		EXT3_I(inode)->i_disksize = pos + copied;
		mark_inode_dirty(inode);
	}
}