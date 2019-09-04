#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct TYPE_5__ {int /*<<< orphan*/  v_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  VISHARDLINK ; 
 int /*<<< orphan*/  vnode_lock_spin (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_unlock (TYPE_1__*) ; 

void vnode_setmultipath(vnode_t vp)
{
	vnode_lock_spin(vp);

	/*
	 * In theory, we're changing the vnode's identity as far as the
	 * name cache is concerned, so we ought to grab the name cache lock
	 * here.  However, there is already a race, and grabbing the name
	 * cache lock only makes the race window slightly smaller.
	 *
	 * The race happens because the vnode already exists in the name
	 * cache, and could be found by one thread before another thread
	 * can set the hard link flag.
	 */

	vp->v_flag |= VISHARDLINK;

	vnode_unlock(vp);
}