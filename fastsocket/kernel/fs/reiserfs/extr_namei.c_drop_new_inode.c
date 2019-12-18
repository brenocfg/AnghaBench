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
struct inode {int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  vfs_dq_drop (struct inode*) ; 

__attribute__((used)) static int drop_new_inode(struct inode *inode)
{
	vfs_dq_drop(inode);
	make_bad_inode(inode);
	inode->i_flags |= S_NOQUOTA;
	iput(inode);
	return 0;
}