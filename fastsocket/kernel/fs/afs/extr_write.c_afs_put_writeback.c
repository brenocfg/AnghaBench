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
struct afs_writeback {scalar_t__ usage; struct afs_vnode* vnode; } ;
struct afs_vnode {int /*<<< orphan*/  writeback_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,scalar_t__) ; 
 int /*<<< orphan*/  afs_free_writeback (struct afs_writeback*) ; 
 int /*<<< orphan*/  afs_unlink_writeback (struct afs_writeback*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void afs_put_writeback(struct afs_writeback *wb)
{
	struct afs_vnode *vnode = wb->vnode;

	_enter("{%d}", wb->usage);

	spin_lock(&vnode->writeback_lock);
	if (--wb->usage == 0)
		afs_unlink_writeback(wb);
	else
		wb = NULL;
	spin_unlock(&vnode->writeback_lock);
	if (wb)
		afs_free_writeback(wb);
}