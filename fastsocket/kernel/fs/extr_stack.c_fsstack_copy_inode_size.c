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
struct inode {int /*<<< orphan*/  i_blocks; } ;

/* Variables and functions */
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 

void fsstack_copy_inode_size(struct inode *dst, const struct inode *src)
{
	i_size_write(dst, i_size_read((struct inode *)src));
	dst->i_blocks = src->i_blocks;
}