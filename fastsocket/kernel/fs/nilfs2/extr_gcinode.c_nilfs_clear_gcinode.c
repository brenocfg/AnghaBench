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
 int /*<<< orphan*/  nilfs_mdt_clear (struct inode*) ; 
 int /*<<< orphan*/  nilfs_mdt_destroy (struct inode*) ; 

void nilfs_clear_gcinode(struct inode *inode)
{
	nilfs_mdt_clear(inode);
	nilfs_mdt_destroy(inode);
}