#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  permits_lock; struct afs_permits* permits; TYPE_1__ fid; } ;
struct afs_permits {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*) ; 
 int /*<<< orphan*/  afs_zap_permits ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct afs_permits*,int /*<<< orphan*/ *) ; 

void afs_clear_permits(struct afs_vnode *vnode)
{
	struct afs_permits *permits;

	_enter("{%x:%u}", vnode->fid.vid, vnode->fid.vnode);

	mutex_lock(&vnode->permits_lock);
	permits = vnode->permits;
	rcu_assign_pointer(vnode->permits, NULL);
	mutex_unlock(&vnode->permits_lock);

	if (permits)
		call_rcu(&permits->rcu, afs_zap_permits);
	_leave("");
}