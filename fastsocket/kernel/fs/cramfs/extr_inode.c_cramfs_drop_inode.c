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
struct inode {int i_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_delete_inode (struct inode*) ; 
 int /*<<< orphan*/  generic_drop_inode (struct inode*) ; 

__attribute__((used)) static void cramfs_drop_inode(struct inode *inode)
{
	if (inode->i_ino == 1)
		generic_delete_inode(inode);
	else
		generic_drop_inode(inode);
}