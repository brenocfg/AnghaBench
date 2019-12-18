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
struct inode {scalar_t__ i_state; int /*<<< orphan*/  i_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ I_CLEAR ; 
 scalar_t__ atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  iput_final (struct inode*) ; 

void iput(struct inode *inode)
{
	if (inode) {
		BUG_ON(inode->i_state == I_CLEAR);

		if (atomic_dec_and_lock(&inode->i_count, &inode_lock))
			iput_final(inode);
	}
}