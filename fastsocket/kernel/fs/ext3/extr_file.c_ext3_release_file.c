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
struct inode {int /*<<< orphan*/  i_writecount; int /*<<< orphan*/  i_mapping; } ;
struct file {int f_mode; scalar_t__ private_data; } ;
struct TYPE_2__ {int i_state; int /*<<< orphan*/  truncate_mutex; } ;

/* Variables and functions */
 TYPE_1__* EXT3_I (struct inode*) ; 
 int EXT3_STATE_FLUSH_ON_CLOSE ; 
 int FMODE_WRITE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ext3_discard_reservation (struct inode*) ; 
 int /*<<< orphan*/  ext3_htree_free_dir_info (scalar_t__) ; 
 int /*<<< orphan*/  filemap_flush (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dx (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ext3_release_file (struct inode * inode, struct file * filp)
{
	if (EXT3_I(inode)->i_state & EXT3_STATE_FLUSH_ON_CLOSE) {
		filemap_flush(inode->i_mapping);
		EXT3_I(inode)->i_state &= ~EXT3_STATE_FLUSH_ON_CLOSE;
	}
	/* if we are the last writer on the inode, drop the block reservation */
	if ((filp->f_mode & FMODE_WRITE) &&
			(atomic_read(&inode->i_writecount) == 1))
	{
		mutex_lock(&EXT3_I(inode)->truncate_mutex);
		ext3_discard_reservation(inode);
		mutex_unlock(&EXT3_I(inode)->truncate_mutex);
	}
	if (is_dx(inode) && filp->private_data)
		ext3_htree_free_dir_info(filp->private_data);

	return 0;
}