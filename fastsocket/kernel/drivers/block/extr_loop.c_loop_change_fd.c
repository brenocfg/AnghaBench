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
struct loop_device {scalar_t__ lo_state; int lo_flags; struct file* lo_backing_file; } ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct file {TYPE_1__* f_mapping; } ;
struct block_device {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLKRRPART ; 
 int EBADF ; 
 int EINVAL ; 
 int ENXIO ; 
 int LO_FLAGS_READ_ONLY ; 
 scalar_t__ Lo_bound ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct file* fget (unsigned int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 scalar_t__ get_loop_size (struct loop_device*,struct file*) ; 
 int /*<<< orphan*/  ioctl_by_bdev (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int loop_switch (struct loop_device*,struct file*) ; 
 scalar_t__ max_part ; 

__attribute__((used)) static int loop_change_fd(struct loop_device *lo, struct block_device *bdev,
			  unsigned int arg)
{
	struct file	*file, *old_file;
	struct inode	*inode;
	int		error;

	error = -ENXIO;
	if (lo->lo_state != Lo_bound)
		goto out;

	/* the loop device has to be read-only */
	error = -EINVAL;
	if (!(lo->lo_flags & LO_FLAGS_READ_ONLY))
		goto out;

	error = -EBADF;
	file = fget(arg);
	if (!file)
		goto out;

	inode = file->f_mapping->host;
	old_file = lo->lo_backing_file;

	error = -EINVAL;

	if (!S_ISREG(inode->i_mode) && !S_ISBLK(inode->i_mode))
		goto out_putf;

	/* size of the new backing store needs to be the same */
	if (get_loop_size(lo, file) != get_loop_size(lo, old_file))
		goto out_putf;

	/* and ... switch */
	error = loop_switch(lo, file);
	if (error)
		goto out_putf;

	fput(old_file);
	if (max_part > 0)
		ioctl_by_bdev(bdev, BLKRRPART, 0);
	return 0;

 out_putf:
	fput(file);
 out:
	return error;
}