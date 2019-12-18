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
struct vnode {int v_nc_generation; } ;
struct componentname {scalar_t__ cn_hash; int /*<<< orphan*/  cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAME_CACHE_LOCK () ; 
 int /*<<< orphan*/  NAME_CACHE_UNLOCK () ; 
 int /*<<< orphan*/  cache_enter_locked (struct vnode*,struct vnode*,struct componentname*,int /*<<< orphan*/ *) ; 
 scalar_t__ hash_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cache_enter_with_gen(struct vnode *dvp, struct vnode *vp, struct componentname *cnp, int gen)
{

        if (cnp->cn_hash == 0)
	        cnp->cn_hash = hash_string(cnp->cn_nameptr, cnp->cn_namelen);

	NAME_CACHE_LOCK();

	if (dvp->v_nc_generation == gen)
	        (void)cache_enter_locked(dvp, vp, cnp, NULL);

	NAME_CACHE_UNLOCK();
}