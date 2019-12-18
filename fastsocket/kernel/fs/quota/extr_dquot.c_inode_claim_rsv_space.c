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
struct inode {int /*<<< orphan*/  i_lock; } ;
typedef  scalar_t__ qsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  __inode_add_bytes (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/ * inode_reserved_space (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void inode_claim_rsv_space(struct inode *inode, qsize_t number)
{
	spin_lock(&inode->i_lock);
	*inode_reserved_space(inode) -= number;
	__inode_add_bytes(inode, number);
	spin_unlock(&inode->i_lock);
}