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
typedef  int /*<<< orphan*/  vnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  NOTE_WRITE ; 
 int /*<<< orphan*/  VQ_MOUNT ; 
 int /*<<< orphan*/  lock_vnode_and_post (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_event_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,intptr_t) ; 

void
vfs_notify_mount(vnode_t pdvp)
{
	vfs_event_signal(NULL, VQ_MOUNT, (intptr_t)NULL);
	lock_vnode_and_post(pdvp, NOTE_WRITE);
}