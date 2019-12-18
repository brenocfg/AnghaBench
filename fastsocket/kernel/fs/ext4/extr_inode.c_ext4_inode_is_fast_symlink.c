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
struct inode {int i_blocks; int /*<<< orphan*/  i_mode; TYPE_1__* i_sb; } ;
struct TYPE_4__ {scalar_t__ i_file_acl; } ;
struct TYPE_3__ {int s_blocksize; } ;

/* Variables and functions */
 TYPE_2__* EXT4_I (struct inode*) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_inode_is_fast_symlink(struct inode *inode)
{
	int ea_blocks = EXT4_I(inode)->i_file_acl ?
		(inode->i_sb->s_blocksize >> 9) : 0;

	return (S_ISLNK(inode->i_mode) && inode->i_blocks - ea_blocks == 0);
}