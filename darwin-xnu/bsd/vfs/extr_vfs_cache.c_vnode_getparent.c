#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
struct TYPE_6__ {int v_id; struct TYPE_6__* v_parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_CACHE_LOCK_SHARED () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 TYPE_1__* NULLVP ; 
 scalar_t__ vnode_getwithvid (TYPE_1__*,int) ; 

vnode_t
vnode_getparent(vnode_t vp)
{
        vnode_t pvp = NULLVP;
	int	pvid;

	NAME_CACHE_LOCK_SHARED();
	/*
	 * v_parent is stable behind the name_cache lock
	 * however, the only thing we can really guarantee
	 * is that we've grabbed a valid iocount on the
	 * parent of 'vp' at the time we took the name_cache lock...
	 * once we drop the lock, vp could get re-parented
	 */
	if ( (pvp = vp->v_parent) != NULLVP ) {
	        pvid = pvp->v_id;

		NAME_CACHE_UNLOCK();

		if (vnode_getwithvid(pvp, pvid) != 0)
		        pvp = NULL;
	} else
	        NAME_CACHE_UNLOCK();
	return (pvp);
}