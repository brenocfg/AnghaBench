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
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* ecryptfs_inode_to_lower (struct inode*) ; 

int ecryptfs_inode_test(struct inode *inode, void *candidate_lower_inode)
{
	if ((ecryptfs_inode_to_lower(inode)
	     == (struct inode *)candidate_lower_inode))
		return 1;
	else
		return 0;
}