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
struct inode {int /*<<< orphan*/  i_ino; } ;
struct cramfs_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRAMINO (struct cramfs_inode*) ; 

__attribute__((used)) static int cramfs_iget5_set(struct inode *inode, void *opaque)
{
	struct cramfs_inode *cramfs_inode = opaque;
	inode->i_ino = CRAMINO(cramfs_inode);
	return 0;
}