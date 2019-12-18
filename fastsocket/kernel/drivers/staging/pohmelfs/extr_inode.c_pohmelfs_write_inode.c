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
struct pohmelfs_inode {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct pohmelfs_inode* POHMELFS_I (struct inode*) ; 
 int /*<<< orphan*/  pohmelfs_write_create_inode (struct pohmelfs_inode*) ; 
 int /*<<< orphan*/  pohmelfs_write_inode_create_children (struct inode*) ; 

__attribute__((used)) static int pohmelfs_write_inode(struct inode *inode, int sync)
{
	struct pohmelfs_inode *pi = POHMELFS_I(inode);

	pohmelfs_write_create_inode(pi);
	pohmelfs_write_inode_create_children(inode);

	return 0;
}