#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {TYPE_2__* i_sb; scalar_t__* i_dquot; } ;
struct TYPE_4__ {TYPE_1__* dq_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* drop ) (struct inode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_NOQUOTA (struct inode*) ; 
 int MAXQUOTAS ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 

void vfs_dq_drop(struct inode *inode)
{
	/* Here we can get arbitrary inode from clear_inode() so we have
	 * to be careful. OTOH we don't need locking as quota operations
	 * are allowed to change only at mount time */
	if (!IS_NOQUOTA(inode) && inode->i_sb && inode->i_sb->dq_op
	    && inode->i_sb->dq_op->drop) {
		int cnt;
		/* Test before calling to rule out calls from proc and such
                 * where we are not allowed to block. Note that this is
		 * actually reliable test even without the lock - the caller
		 * must assure that nobody can come after the DQUOT_DROP and
		 * add quota pointers back anyway */
		for (cnt = 0; cnt < MAXQUOTAS; cnt++)
			if (inode->i_dquot[cnt])
				break;
		if (cnt < MAXQUOTAS)
			inode->i_sb->dq_op->drop(inode);
	}
}