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
struct super_block {int dummy; } ;
struct inode {int i_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ INODE_VERSION (struct inode*) ; 
 int I_NEW ; 
 scalar_t__ MINIX_V1 ; 
 struct inode* V1_minix_iget (struct inode*) ; 
 struct inode* V2_minix_iget (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 

struct inode *minix_iget(struct super_block *sb, unsigned long ino)
{
	struct inode *inode;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);
	if (!(inode->i_state & I_NEW))
		return inode;

	if (INODE_VERSION(inode) == MINIX_V1)
		return V1_minix_iget(inode);
	else
		return V2_minix_iget(inode);
}