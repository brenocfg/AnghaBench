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
 TYPE_1__* EXT3_I (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ext3_xattr_block_list (struct inode*,char*,size_t) ; 
 int ext3_xattr_ibody_list (struct inode*,char*,size_t) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ext3_xattr_list(struct inode *inode, char *buffer, size_t buffer_size)
{
	int i_error, b_error;

	down_read(&EXT3_I(inode)->xattr_sem);
	i_error = ext3_xattr_ibody_list(inode, buffer, buffer_size);
	if (i_error < 0) {
		b_error = 0;
	} else {
		if (buffer) {
			buffer += i_error;
			buffer_size -= i_error;
		}
		b_error = ext3_xattr_block_list(inode, buffer, buffer_size);
		if (b_error < 0)
			i_error = 0;
	}
	up_read(&EXT3_I(inode)->xattr_sem);
	return i_error + b_error;
}