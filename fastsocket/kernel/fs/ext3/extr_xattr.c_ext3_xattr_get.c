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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xattr_sem; } ;

/* Variables and functions */
 int ENODATA ; 
 TYPE_1__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ext3_xattr_block_get (struct inode*,int,char const*,void*,size_t) ; 
 int ext3_xattr_ibody_get (struct inode*,int,char const*,void*,size_t) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int
ext3_xattr_get(struct inode *inode, int name_index, const char *name,
	       void *buffer, size_t buffer_size)
{
	int error;

	down_read(&EXT3_I(inode)->xattr_sem);
	error = ext3_xattr_ibody_get(inode, name_index, name, buffer,
				     buffer_size);
	if (error == -ENODATA)
		error = ext3_xattr_block_get(inode, name_index, name, buffer,
					     buffer_size);
	up_read(&EXT3_I(inode)->xattr_sem);
	return error;
}