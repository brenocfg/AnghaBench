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
 int /*<<< orphan*/  ecryptfs_inode_to_lower (struct inode*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecryptfs_clear_inode(struct inode *inode)
{
	iput(ecryptfs_inode_to_lower(inode));
}