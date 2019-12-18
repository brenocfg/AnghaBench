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
 int /*<<< orphan*/  vnode_lock_spin (int /*<<< orphan*/ ) ; 
 int vnode_put_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnode_unlock (int /*<<< orphan*/ ) ; 

int
vnode_put(vnode_t vp)
{
        int retval;

	vnode_lock_spin(vp);
	retval = vnode_put_locked(vp);
	vnode_unlock(vp);

	return(retval);
}