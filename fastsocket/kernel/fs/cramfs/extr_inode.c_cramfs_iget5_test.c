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
struct cramfs_inode {int dummy; } ;

/* Variables and functions */
 int CRAMINO (struct cramfs_inode*) ; 

__attribute__((used)) static int cramfs_iget5_test(struct inode *inode, void *opaque)
{
	struct cramfs_inode *cramfs_inode = opaque;
	return inode->i_ino == CRAMINO(cramfs_inode) && inode->i_ino != 1;
}